/* 
 * Copyright 2021 seamus@bumblestack.com, Corvideon Limited.
 * Portions of this code were originally created by the OpenNARS authors under the MIT License.

 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "nars_memory.h"

//Concepts in main memory:
PriorityQueue concepts;
//cycling events cycling in main memory:
PriorityQueue cycling_belief_events;
PriorityQueue cycling_goal_events;
//Hashtable of concepts used for fast retrieval of concepts via term:
HashTable HTconcepts;
//Input event fifo:
FIFO belief_events;
//Operations
Operation operations[OPERATIONS_MAX];
//Parameters
bool PRINT_DERIVATIONS = DEBUG_MODE;
bool PRINT_INPUT = DEBUG_MODE;
//Storage arrays for the datastructures
Concept concept_storage[CONCEPTS_MAX];
Item concept_items_storage[CONCEPTS_MAX];
Event cycling_belief_event_storage[CYCLING_BELIEF_EVENTS_MAX];
Item cycling_belief_event_items_storage[CYCLING_BELIEF_EVENTS_MAX];
Event cycling_goal_event_storage[CYCLING_GOAL_EVENTS_MAX];
Item cycling_goal_event_items_storage[CYCLING_GOAL_EVENTS_MAX];
//Dynamic concept firing threshold
double conceptPriorityThreshold = 0.0;
//Special ontology handling if demanded
bool ontology_handling = false;

static void
Memory_ResetEvents()
{
	belief_events = (FIFO) {0};
	PriorityQueue_INIT(&cycling_belief_events, cycling_belief_event_items_storage, CYCLING_BELIEF_EVENTS_MAX);
	PriorityQueue_INIT(&cycling_goal_events, cycling_goal_event_items_storage, CYCLING_GOAL_EVENTS_MAX);
	for (int i = 0; i < CYCLING_BELIEF_EVENTS_MAX; i++)
	{
		cycling_belief_event_storage[i] = (Event) {0};
		cycling_belief_events.items[i] = (Item) {.address = &(cycling_belief_event_storage[i])};
	}
	for (int i = 0; i < CYCLING_GOAL_EVENTS_MAX; i++)
	{
		cycling_goal_event_storage[i] = (Event) {0};
		cycling_goal_events.items[i] = (Item) {.address = &(cycling_goal_event_storage[i])};
	}
}

static void
Memory_ResetConcepts()
{
	PriorityQueue_INIT(&concepts, concept_items_storage, CONCEPTS_MAX);
	for (int i = 0; i < CONCEPTS_MAX; i++)
	{
		concept_storage[i] = (Concept) {0};
		concepts.items[i] = (Item) {.address = &(concept_storage[i])};
	}
}

int concept_id = 0;
VMItem *HTconcepts_storageptrs[CONCEPTS_MAX];
VMItem HTconcepts_storage[CONCEPTS_MAX];
VMItem *HTconcepts_HT[CONCEPTS_HASHTABLE_BUCKETS]; //the hash of the concept term is the index

void
Memory_INIT()
{
	HashTable_INIT(&HTconcepts, HTconcepts_storage, HTconcepts_storageptrs, HTconcepts_HT, CONCEPTS_HASHTABLE_BUCKETS,
	               CONCEPTS_MAX, (Equal) Term_Equal, (Hash) Term_Hash);
	conceptPriorityThreshold = 0.0;
	Memory_ResetConcepts();
	Memory_ResetEvents();
	InvertedAtomIndex_INIT();
	for (int i = 0; i < OPERATIONS_MAX; i++)
	{
		operations[i] = (Operation) {0};
	}
	concept_id = 0;
	ontology_handling = false;
}

Concept *
Memory_FindConceptByTerm(Term *term)
{
	return HashTable_Get(&HTconcepts, term);
}

Concept *
Memory_Conceptualize(Term *term, long currentTime)
{
	if (Narsese_getOperationID(term)) //don't conceptualize operations
	{
		return NULL;
	}
	Concept *ret = Memory_FindConceptByTerm(term);
	if (ret == NULL)
	{
		Concept *recycleConcept = NULL;
		//try to add it, and if successful add to voting structure
		PriorityQueue_Push_Feedback feedback = PriorityQueue_Push(&concepts, 1);
		if (feedback.added)
		{
			recycleConcept = feedback.addedItem.address;
			//if something was evicted in the adding process delete from hashmap first
			if (feedback.evicted)
			{
				IS_SYSTEM_IN_DEBUG_MODE(assert(HashTable_Get(&HTconcepts, &recycleConcept->term) != NULL,
				                               "VMItem to delete does not exist!");)
				HashTable_Delete(&HTconcepts, &recycleConcept->term);
				IS_SYSTEM_IN_DEBUG_MODE(assert(HashTable_Get(&HTconcepts, &recycleConcept->term) == NULL,
				                               "VMItem to delete was not deleted!");)
				//and also delete from inverted atom index:
				InvertedAtomIndex_RemoveConcept(recycleConcept->term, recycleConcept);
			}
			//Add term to inverted atom index as well:
			InvertedAtomIndex_AddConcept(*term, recycleConcept);
			//proceed with recycling of the concept in the priority queue
			*recycleConcept = (Concept) {0};
			recycleConcept->term = *term;
			recycleConcept->id = concept_id;
			recycleConcept->usage = (Usage) {.useCount = 1, .lastUsed = currentTime};
			concept_id++;
			//also add added concept to HashMap:
			IS_SYSTEM_IN_DEBUG_MODE(
				assert(HashTable_Get(&HTconcepts, &recycleConcept->term) == NULL, "VMItem to add already exists!");)
			HashTable_Set(&HTconcepts, &recycleConcept->term, recycleConcept);
			IS_SYSTEM_IN_DEBUG_MODE(assert(HashTable_Get(&HTconcepts, &recycleConcept->term) != NULL,
			                               "VMItem to add was not added!");)
			return recycleConcept;
		}
	}
	else
	{
		return ret;
	}
	return NULL;
}

Event selectedBeliefs[BELIEF_EVENT_SELECTIONS]; //better to be global
double selectedBeliefsPriority[BELIEF_EVENT_SELECTIONS]; //better to be global
int beliefsSelectedCnt = 0;
Event selectedGoals[GOAL_EVENT_SELECTIONS]; //better to be global
double selectedGoalsPriority[GOAL_EVENT_SELECTIONS]; //better to be global
int goalsSelectedCnt = 0;

static bool
Memory_containsEvent(PriorityQueue *queue, Event *event)
{
	for (int i = 0; i < queue->itemsAmount; i++)
	{
		if (Event_Equal(event, queue->items[i].address))
		{
			return true;
		}
	}
	return false;
}

//Add event for cycling through the system (inference and context)
//called by addEvent for eternal knowledge
bool
Memory_addCyclingEvent(Event *e, double priority, long currentTime)
{
	assert(e->type == EVENT_TYPE_BELIEF || e->type == EVENT_TYPE_GOAL,
	       "Only belief and goals events can be added to cycling events queue!");
	if ((e->type == EVENT_TYPE_BELIEF && Memory_containsEvent(&cycling_belief_events, e)) ||
		(e->type == EVENT_TYPE_GOAL && Memory_containsEvent(&cycling_goal_events, e))) //avoid duplicate derivations
	{
		return false;
	}
	Concept *c = Memory_FindConceptByTerm(&e->term);
	if (c != NULL)
	{
		if (e->type == EVENT_TYPE_BELIEF && c->belief.type != EVENT_TYPE_DELETED &&
			((e->occurrenceTime == OCCURRENCE_ETERNAL && c->belief.truth.confidence > e->truth.confidence) ||
				(e->occurrenceTime != OCCURRENCE_ETERNAL &&
					Truth_Projection(c->belief_spike.truth, c->belief_spike.occurrenceTime, currentTime).confidence >
						Truth_Projection(e->truth, e->occurrenceTime, currentTime).confidence)))
		{
			return false; //the belief has a higher confidence and was already revised up (or a cyclic transformation happened!), get rid of the event!
		}   //more radical than OpenNARS!
		if (e->type == EVENT_TYPE_GOAL && c->goal_spike.type != EVENT_TYPE_DELETED &&
			((e->occurrenceTime == OCCURRENCE_ETERNAL && c->goal_spike.truth.confidence > e->truth.confidence) ||
				(e->occurrenceTime != OCCURRENCE_ETERNAL &&
					Truth_Projection(c->goal_spike.truth, c->goal_spike.occurrenceTime, currentTime).confidence >
						Truth_Projection(e->truth, e->occurrenceTime, currentTime).confidence)))
		{
			return false; //the belief has a higher confidence and was already revised up (or a cyclic transformation happened!), get rid of the event!
		}   //more radical than OpenNARS!
	}
	PriorityQueue *priority_queue = e->type == EVENT_TYPE_BELIEF ? &cycling_belief_events : &cycling_goal_events;
	PriorityQueue_Push_Feedback feedback = PriorityQueue_Push(priority_queue, priority);
	if (feedback.added)
	{
		Event *toRecyle = feedback.addedItem.address;
		*toRecyle = *e;
		return true;
	}
	return false;
}

static void
Memory_printAddedKnowledge(Term *term, char type, Truth *truth, long occurrenceTime, double occurrenceTimeOffset,
                           double priority, bool input, bool derived, bool revised, bool controlInfo)
{
	if (((input && PRINT_INPUT) || PRINT_DERIVATIONS) && priority > PRINT_DERIVATIONS_PRIORITY_THRESHOLD &&
		(input || derived || revised))
	{
		if (controlInfo)
			fputs(revised ? "Revised: " : (input ? "Input: " : "Derived: "), stdout);
		if (Narsese_copulaEquals(term->atoms[0], '$'))
			printf("occurrenceTimeOffset=(%f) ", occurrenceTimeOffset);
		Narsese_PrintTerm(term);
		fputs((type == EVENT_TYPE_BELIEF ? ". " : "! "), stdout);
		if (occurrenceTime != OCCURRENCE_ETERNAL)
		{
			printf(":|: occurrenceTime=(%ld) ", occurrenceTime);
		}
		if (controlInfo)
		{
			printf("priority=(%f) ", priority);
			Truth_Print(truth);
		}
		else
		{
			Truth_Print2(truth);
		}
		fflush(stdout);
	}
}

void
Memory_printAddedEvent(Event *event, double priority, bool input, bool derived, bool revised, bool controlInfo)
{
	Memory_printAddedKnowledge(&event->term, event->type, &event->truth, event->occurrenceTime, 0, priority, input,
	                           derived, revised, controlInfo);
}

void
Memory_printAddedImplication(Term *implication, Truth *truth, double occurrenceTimeOffset, double priority, bool input,
                             bool revised, bool controlInfo)
{
	Memory_printAddedKnowledge(implication, EVENT_TYPE_BELIEF, truth, OCCURRENCE_ETERNAL, occurrenceTimeOffset,
	                           priority, input, true, revised, controlInfo);
}

void
Memory_ProcessNewBeliefEvent(Event *event, long currentTime, double priority, double occurrenceTimeOffset, bool input,
                             bool predicted, bool isImplication)
{
	bool eternalInput = input && event->occurrenceTime == OCCURRENCE_ETERNAL;
	Event eternal_event = *event;
	if (event->occurrenceTime != OCCURRENCE_ETERNAL)
	{
		eternal_event.occurrenceTime = OCCURRENCE_ETERNAL;
		eternal_event.truth = Truth_Eternalize(event->truth);
	}
	if (event->isUserKnowledge)
	{
		ontology_handling = true;
	}
	if (isImplication)
	{
		//get predicate and add the subject to precondition table as an implication
		Term subject = Term_ExtractSubterm(&event->term, 1);
		Term predicate = Term_ExtractSubterm(&event->term, 2);
		Concept *target_concept = Memory_Conceptualize(&predicate, currentTime);
		if (target_concept != NULL)
		{
			target_concept->usage = Usage_use(target_concept->usage, currentTime, eternalInput);
			Implication imp = {.truth = eternal_event.truth,
				.stamp = eternal_event.stamp,
				.occurrenceTimeOffset = occurrenceTimeOffset,
				.creationTime = currentTime,
				.isUserKnowledge = event->isUserKnowledge};
			Term sourceConceptTerm = subject;
			//now extract operation id
			int opi = 0;
			if (Narsese_copulaEquals(subject.atoms[0], '+')) //sequence
			{
				Term potential_op = Term_ExtractSubterm(&subject, 2);
				if (Narsese_isOperation(&potential_op)) //atom starts with ^, making it an operator
				{
					opi = Narsese_getOperationID(&potential_op); //"<(a * b) --> ^op>" to ^op index
					sourceConceptTerm = Term_ExtractSubterm(&subject, 1); //gets rid of op as MSC links cannot use it
				}
				else
				{
					sourceConceptTerm = subject;
				}
			}
			else
			{
				sourceConceptTerm = subject;
			}
			Concept *source_concept = Memory_Conceptualize(&sourceConceptTerm, currentTime);
			if (source_concept != NULL)
			{
				source_concept->usage = Usage_use(source_concept->usage, currentTime, eternalInput);
				source_concept->hasUserKnowledge |= event->isUserKnowledge;
				target_concept->hasUserKnowledge |= event->isUserKnowledge;
				imp.sourceConceptId = source_concept->id;
				imp.sourceConcept = source_concept;
				imp.term = event->term;
				Implication *revised = Table_AddAndRevise(&target_concept->precondition_beliefs[opi], &imp);
				if (revised != NULL)
				{
					bool wasRevised = revised->truth.confidence > event->truth.confidence ||
						revised->truth.confidence == MAX_CONFIDENCE;
					Memory_printAddedImplication(&event->term, &event->truth, occurrenceTimeOffset, priority, input,
					                             false, true);
					if (wasRevised)
						Memory_printAddedImplication(&revised->term, &revised->truth, revised->occurrenceTimeOffset,
						                             priority, input, true, true);
				}
			}
		}
	}
	else
	{
		Concept *c = Memory_Conceptualize(&event->term, currentTime);
		if (c != NULL)
		{
			c->usage = Usage_use(c->usage, currentTime, eternalInput);
			c->priority = MAX(c->priority, priority);
			c->hasUserKnowledge |= event->isUserKnowledge;
			if (event->occurrenceTime != OCCURRENCE_ETERNAL && event->occurrenceTime <= currentTime)
			{
				c->belief_spike = Inference_RevisionAndChoice(&c->belief_spike, event, currentTime, NULL);
				c->belief_spike.creationTime = currentTime; //for metrics
			}
			if (event->occurrenceTime != OCCURRENCE_ETERNAL && event->occurrenceTime > currentTime)
			{
				c->predicted_belief = Inference_RevisionAndChoice(&c->predicted_belief, event, currentTime, NULL);
				c->predicted_belief.creationTime = currentTime;
			}
			bool revision_happened = false;
			c->belief = Inference_RevisionAndChoice(&c->belief, &eternal_event, currentTime, &revision_happened);
			c->belief.creationTime = currentTime; //for metrics
			if (revision_happened)
			{
				Memory_AddEvent(&c->belief, currentTime, priority, 0, false, false, false, true, predicted);
			}
			//BEGIN SPECIAL HANDLING FOR USER KNOWLEDGE
			if (ontology_handling && !predicted)
			{
				for (int j = 0; j < concepts.itemsAmount; j++)
				{
					Concept *cpost = concepts.items[j].address;
					if (cpost->hasUserKnowledge)
					{
						for (int k = 0; k < cpost->precondition_beliefs[0].itemsAmount; k++)
						{
							Implication *imp = &cpost->precondition_beliefs[0].array[k];
							if (imp->isUserKnowledge)
							{
								Term subject = Term_ExtractSubterm(&imp->term, 1);
								if (Variable_Unify(&subject, &event->term).success)
								{
									assert(Narsese_copulaEquals(imp->term.atoms[0], '$'),
									       "Not a valid implication term!");
									Term precondition_with_op = Term_ExtractSubterm(&imp->term, 1);
									Term precondition = Narsese_GetPreconditionWithoutOp(&precondition_with_op);
									Substitution subs = Variable_Unify(&precondition, &event->term);
									if (subs.success)
									{
										Implication updated_imp = *imp;
										bool success;
										updated_imp.term = Variable_ApplySubstitute(updated_imp.term, subs, &success);
										if (success)
										{
											Event predicted = Inference_BeliefDeduction(event, &updated_imp);
											Memory_AddEvent(&predicted,
											                currentTime,
											                priority * Truth_Expectation(imp->truth) *
												                Truth_Expectation(predicted.truth),
											                0,
											                false,
											                true,
											                false,
											                false,
											                true);
										}
									}
									break;
								}
							}
						}
					}
				}
			}
			//END SPECIAL HANDLING FOR USER KNOWLEDGE
		}
	}
}

void
Memory_AddEvent(Event *event, long currentTime, double priority, double occurrenceTimeOffset, bool input, bool derived,
                bool readded, bool revised, bool predicted)
{
	if (readded) //readded events get durability applied, they already got complexity-penalized
	{
		priority *= EVENT_DURABILITY_ON_USAGE;
	}
	else if (!revised &&
		!input) //derivations get penalized by complexity as well, but revised ones not as they already come from an input or derivation
	{
		double complexity = Term_Complexity(&event->term);
		priority *= 1.0 / log2(1.0 + complexity);
	}
	if (event->truth.confidence < MIN_CONFIDENCE || priority <= MIN_PRIORITY || priority == 0.0)
	{
		return;
	}
	if (event->occurrenceTime != OCCURRENCE_ETERNAL)
	{
		if (input)
		{
			//process event
			if (event->type == EVENT_TYPE_BELIEF)
			{
				FIFO_Add(event, &belief_events); //not revised yet
			}
		}
	}
	bool isImplication = Narsese_copulaEquals(event->term.atoms[0], '$');
	if (!readded && !isImplication) //print new tasks
	{
		Memory_printAddedEvent(event, priority, input, derived, revised, true);
	}
	if (event->type == EVENT_TYPE_BELIEF)
	{
		if (!readded)
		{
			Memory_ProcessNewBeliefEvent(event, currentTime, priority, occurrenceTimeOffset, input, predicted,
			                             isImplication);
			if (isImplication)
			{
				return;
			}
		}
		Memory_addCyclingEvent(event, priority, currentTime);
	}
	if (event->type == EVENT_TYPE_GOAL)
	{
		assert(event->occurrenceTime != OCCURRENCE_ETERNAL, "Eternal goals are not supported");
		Memory_addCyclingEvent(event, priority, currentTime);
	}
	assert(event->type == EVENT_TYPE_BELIEF || event->type == EVENT_TYPE_GOAL, "Errornous event type");
}

void
Memory_AddInputEvent(Event *event, double occurrenceTimeOffset, long currentTime)
{
	Memory_AddEvent(event, currentTime, 1, occurrenceTimeOffset, true, false, false, false, false);
}

bool
Memory_ImplicationValid(Implication *imp)
{
	return imp->sourceConceptId == ((Concept *) imp->sourceConcept)->id;
}
