/* 
 * The MIT License
 *
 * Copyright 2020 The OpenNARS authors.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
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
PriorityQueue g_concepts;

//cycling events cycling in main memory:
PriorityQueue g_cyclingBeliefEvents;
PriorityQueue g_cyclingGoalEvents;

//Hashtable of g_concepts used for fast retrieval of g_concepts via term:
HashTable g_hashtableConceptsStruct;

//Input event fifo:
FIFO g_beliefEvents;

//Operations
Operation g_operations[OPERATIONS_MAX];

//Parameters
bool PRINT_DERIVATIONS = DEBUG_MODE;
bool PRINT_INPUT = DEBUG_MODE;

//Storage arrays for the datastructures
Concept g_conceptStorage[CONCEPTS_MAX];
Item g_conceptItemsStorage[CONCEPTS_MAX];
Event g_cyclingBeliefEventStorage[CYCLING_BELIEF_EVENTS_MAX];
Item g_cyclingBeliefEventItemsStorage[CYCLING_BELIEF_EVENTS_MAX];
Event g_cyclingGoalEventStorage[CYCLING_GOAL_EVENTS_MAX];
Item g_cyclingGoalEventItemsStorage[CYCLING_GOAL_EVENTS_MAX];

//Dynamic concept firing threshold
double g_conceptPriorityThreshold = 0.0;

//Special ontology handling if demanded
bool g_ontologyHandling = false;

// hashtable for concepts internals
int g_conceptId = 0;
VMItem *g_hashtableConceptsStoragePtrs[CONCEPTS_MAX];
VMItem g_hashtableConceptsStorage[CONCEPTS_MAX];
VMItem *g_hashtableConceptsHashtable[CONCEPTS_HASHTABLE_BUCKETS]; //the hash of the concept term is the index

// belief and goal global storage
Event g_selectedBeliefs[BELIEF_EVENT_SELECTIONS]; //better to be global
double g_selectedBeliefsPriority[BELIEF_EVENT_SELECTIONS]; //better to be global
int g_beliefsSelectedCnt = 0;
Event g_selectedGoals[GOAL_EVENT_SELECTIONS]; //better to be global
double g_selectedGoalsPriority[GOAL_EVENT_SELECTIONS]; //better to be global
int g_goalsSelectedCnt = 0;

static void
memory_reset_events()
{
	g_beliefEvents = (FIFO) {0};
	priority_queue_init(&g_cyclingBeliefEvents, g_cyclingBeliefEventItemsStorage, CYCLING_BELIEF_EVENTS_MAX);
	priority_queue_init(&g_cyclingGoalEvents, g_cyclingGoalEventItemsStorage, CYCLING_GOAL_EVENTS_MAX);
	for (int i = 0; i < CYCLING_BELIEF_EVENTS_MAX; i++)
	{
		g_cyclingBeliefEventStorage[i] = (Event) {0};
		g_cyclingBeliefEvents.items[i] = (Item) {.address = &(g_cyclingBeliefEventStorage[i])};
	}
	for (int i = 0; i < CYCLING_GOAL_EVENTS_MAX; i++)
	{
		g_cyclingGoalEventStorage[i] = (Event) {0};
		g_cyclingGoalEvents.items[i] = (Item) {.address = &(g_cyclingGoalEventStorage[i])};
	}
}

static void
memory_reset_concepts()
{
	priority_queue_init(&g_concepts, g_conceptItemsStorage, CONCEPTS_MAX);
	for (int i = 0; i < CONCEPTS_MAX; i++)
	{
		g_conceptStorage[i] = (Concept) {0};
		g_concepts.items[i] = (Item) {.address = &(g_conceptStorage[i])};
	}
}

void
memory_init()
{
	hashtable_init(&g_hashtableConceptsStruct,
	               g_hashtableConceptsStorage,
	               g_hashtableConceptsStoragePtrs,
	               g_hashtableConceptsHashtable,
	               CONCEPTS_HASHTABLE_BUCKETS,
	               CONCEPTS_MAX,
	               (Equal) term_equal,
	               (Hash) term_hash);
	g_conceptPriorityThreshold = 0.0;
	memory_reset_concepts();
	memory_reset_events();
	inverted_atom_index_init();
	for (int i = 0; i < OPERATIONS_MAX; i++)
	{
		g_operations[i] = (Operation) {0};
	}
	g_conceptId = 0;
	g_ontologyHandling = false;
}

Concept *
memory_find_concept_by_term(Term *term)
{
	return hashtable_get(&g_hashtableConceptsStruct, term);
}

Concept *
memory_conceptualise(Term *term, long currentTime)
{
	if (narsese_get_operation_id(term)) //don't conceptualize g_operations
	{
		return NULL;
	}
	Concept *ret = memory_find_concept_by_term(term);
	if (ret == NULL)
	{
		Concept *recycleConcept = NULL;
		//try to add it, and if successful add to voting structure
		PriorityQueuePushFeedback feedback = priority_queue_push(&g_concepts, 1);
		if (feedback.added)
		{
			recycleConcept = feedback.addedItem.address;
			//if something was evicted in the adding process delete from hashmap first
			if (feedback.evicted)
			{
				IS_SYSTEM_IN_DEBUG_MODE(ASSERT(hashtable_get(&g_hashtableConceptsStruct, &recycleConcept->term) != NULL,
				                               "VMItem to delete does not exist!");)
				hashtable_delete(&g_hashtableConceptsStruct, &recycleConcept->term);
				IS_SYSTEM_IN_DEBUG_MODE(ASSERT(hashtable_get(&g_hashtableConceptsStruct, &recycleConcept->term) == NULL,
				                               "VMItem to delete was not deleted!");)
				//and also delete from inverted atom index:
				inverted_atom_index_remove_concept(recycleConcept->term, recycleConcept);
			}
			//Add term to inverted atom index as well:
			inverted_atom_index_add_concept(*term, recycleConcept);
			//proceed with recycling of the concept in the priority queue
			*recycleConcept = (Concept) {0};
			recycleConcept->term = *term;
			recycleConcept->id = g_conceptId;
			recycleConcept->usage = (Usage) {.useCount = 1, .lastUsed = currentTime};
			g_conceptId++;
			//also add added concept to HashMap:
			IS_SYSTEM_IN_DEBUG_MODE(
				ASSERT(hashtable_get(&g_hashtableConceptsStruct, &recycleConcept->term) == NULL, "VMItem to add already exists!");)
			hashtable_set(&g_hashtableConceptsStruct, &recycleConcept->term, recycleConcept);
			IS_SYSTEM_IN_DEBUG_MODE(ASSERT(hashtable_get(&g_hashtableConceptsStruct, &recycleConcept->term) != NULL,
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

static bool
memory_contains_event(PriorityQueue *queue, Event *event)
{
	for (int i = 0; i < queue->itemsAmount; i++)
	{
		if (event_equal(event, queue->items[i].address))
		{
			return true;
		}
	}
	return false;
}

//Add event for cycling through the system (inference and context)
//called by addEvent for eternal knowledge
bool
memory_add_cycling_event(Event *e, double priority, long currentTime)
{
	ASSERT(e->type == EVENT_TYPE_BELIEF || e->type == EVENT_TYPE_GOAL,
	       "Only belief and goals events can be added to cycling events queue!");
	if ((e->type == EVENT_TYPE_BELIEF && memory_contains_event(&g_cyclingBeliefEvents, e)) ||
		(e->type == EVENT_TYPE_GOAL && memory_contains_event(&g_cyclingGoalEvents, e))) //avoid duplicate derivations
	{
		return false;
	}
	Concept *c = memory_find_concept_by_term(&e->term);
	if (c != NULL)
	{
		if (e->type == EVENT_TYPE_BELIEF && c->belief.type != EVENT_TYPE_DELETED &&
			((e->occurrenceTime == OCCURRENCE_ETERNAL && c->belief.truth.confidence > e->truth.confidence) ||
				(e->occurrenceTime != OCCURRENCE_ETERNAL &&
					truth_projection(c->belief_spike.truth, c->belief_spike.occurrenceTime, currentTime).confidence >
						truth_projection(e->truth, e->occurrenceTime, currentTime).confidence)))
		{
			return false; //the belief has a higher confidence and was already revised up (or a cyclic transformation happened!), get rid of the event!
		}   //more radical than OpenNARS!
		if (e->type == EVENT_TYPE_GOAL && c->goal_spike.type != EVENT_TYPE_DELETED &&
			((e->occurrenceTime == OCCURRENCE_ETERNAL && c->goal_spike.truth.confidence > e->truth.confidence) ||
				(e->occurrenceTime != OCCURRENCE_ETERNAL &&
					truth_projection(c->goal_spike.truth, c->goal_spike.occurrenceTime, currentTime).confidence >
						truth_projection(e->truth, e->occurrenceTime, currentTime).confidence)))
		{
			return false; //the belief has a higher confidence and was already revised up (or a cyclic transformation happened!), get rid of the event!
		}   //more radical than OpenNARS!
	}
	PriorityQueue *priority_queue = e->type == EVENT_TYPE_BELIEF ? &g_cyclingBeliefEvents : &g_cyclingGoalEvents;
	PriorityQueuePushFeedback feedback = priority_queue_push(priority_queue, priority);
	if (feedback.added)
	{
		Event *toRecyle = feedback.addedItem.address;
		*toRecyle = *e;
		return true;
	}
	return false;
}

static void
memory_print_added_knowledge(Term *term, char type, Truth *truth, long occurrenceTime, double occurrenceTimeOffset,
                             double priority, bool input, bool derived, bool revised, bool controlInfo)
{
	if (((input && PRINT_INPUT) || PRINT_DERIVATIONS) && priority > PRINT_DERIVATIONS_PRIORITY_THRESHOLD &&
		(input || derived || revised))
	{
		if (controlInfo)
			fputs(revised ? "Revised: " : (input ? "Input: " : "Derived: "), stdout);
		if (narsese_copula_equals(term->atoms[0], '$'))
			printf("occurrenceTimeOffset=(%f) ", occurrenceTimeOffset);
		narsese_print_term(term);
		fputs((type == EVENT_TYPE_BELIEF ? ". " : "! "), stdout);
		if (occurrenceTime != OCCURRENCE_ETERNAL)
		{
			printf(":|: occurrenceTime=(%ld) ", occurrenceTime);
		}
		if (controlInfo)
		{
			printf("priority=(%f) ", priority);
			truth_print(truth);
		}
		else
		{
			truth_print2(truth);
		}
		fflush(stdout);
	}
}

void
memory_print_added_event(Event *event, double priority, bool input, bool derived, bool revised, bool controlInfo)
{
	memory_print_added_knowledge(&event->term, event->type, &event->truth, event->occurrenceTime, 0, priority, input,
	                             derived, revised, controlInfo);
}

void
Memory_printAddedImplication(Term *implication, Truth *truth, double occurrenceTimeOffset, double priority, bool input,
                             bool revised, bool controlInfo)
{
	memory_print_added_knowledge(implication, EVENT_TYPE_BELIEF, truth, OCCURRENCE_ETERNAL, occurrenceTimeOffset,
	                             priority, input, true, revised, controlInfo);
}

void
memory_process_new_belief_event(Event *event, long currentTime, double priority, double occurrenceTimeOffset, bool input,
                                bool predicted, bool isImplication)
{
	bool eternalInput = input && event->occurrenceTime == OCCURRENCE_ETERNAL;
	Event eternal_event = *event;
	if (event->occurrenceTime != OCCURRENCE_ETERNAL)
	{
		eternal_event.occurrenceTime = OCCURRENCE_ETERNAL;
		eternal_event.truth = truth_eternalise(event->truth);
	}
	if (event->isUserKnowledge)
	{
		g_ontologyHandling = true;
	}
	if (isImplication)
	{
		//get predicate and add the subject to precondition table as an implication
		Term subject = term_extract_subterm(&event->term, 1);
		Term predicate = term_extract_subterm(&event->term, 2);
		Concept *target_concept = memory_conceptualise(&predicate, currentTime);
		if (target_concept != NULL)
		{
			target_concept->usage = usage_use(target_concept->usage, currentTime, eternalInput);
			Implication imp = {.truth = eternal_event.truth,
				.stamp = eternal_event.stamp,
				.occurrenceTimeOffset = occurrenceTimeOffset,
				.creationTime = currentTime,
				.isUserKnowledge = event->isUserKnowledge};
			Term sourceConceptTerm = subject;
			//now extract operation id
			int opi = 0;
			if (narsese_copula_equals(subject.atoms[0], '+')) //sequence
			{
				Term potential_op = term_extract_subterm(&subject, 2);
				if (narsese_is_operation(&potential_op)) //atom starts with ^, making it an operator
				{
					opi = narsese_get_operation_id(&potential_op); //"<(a * b) --> ^op>" to ^op index
					sourceConceptTerm = term_extract_subterm(&subject, 1); //gets rid of op as MSC links cannot use it
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
			Concept *source_concept = memory_conceptualise(&sourceConceptTerm, currentTime);
			if (source_concept != NULL)
			{
				source_concept->usage = usage_use(source_concept->usage, currentTime, eternalInput);
				source_concept->hasUserKnowledge |= event->isUserKnowledge;
				target_concept->hasUserKnowledge |= event->isUserKnowledge;
				imp.sourceConceptId = source_concept->id;
				imp.sourceConcept = source_concept;
				imp.term = event->term;
				Implication *revised = table_add_and_revise(&target_concept->precondition_beliefs[opi], &imp);
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
		Concept *c = memory_conceptualise(&event->term, currentTime);
		if (c != NULL)
		{
			c->usage = usage_use(c->usage, currentTime, eternalInput);
			c->priority = MAX(c->priority, priority);
			c->hasUserKnowledge |= event->isUserKnowledge;
			if (event->occurrenceTime != OCCURRENCE_ETERNAL && event->occurrenceTime <= currentTime)
			{
				c->belief_spike = inference_revision_and_choice(&c->belief_spike, event, currentTime, NULL);
				c->belief_spike.creationTime = currentTime; //for metrics
			}
			if (event->occurrenceTime != OCCURRENCE_ETERNAL && event->occurrenceTime > currentTime)
			{
				c->predicted_belief = inference_revision_and_choice(&c->predicted_belief, event, currentTime, NULL);
				c->predicted_belief.creationTime = currentTime;
			}
			bool revision_happened = false;
			c->belief = inference_revision_and_choice(&c->belief, &eternal_event, currentTime, &revision_happened);
			c->belief.creationTime = currentTime; //for metrics
			if (revision_happened)
			{
				memory_add_event(&c->belief, currentTime, priority, 0, false, false, false, true, predicted);
			}
			//BEGIN SPECIAL HANDLING FOR USER KNOWLEDGE
			if (g_ontologyHandling && !predicted)
			{
				for (int j = 0; j < g_concepts.itemsAmount; j++)
				{
					Concept *cpost = g_concepts.items[j].address;
					if (cpost->hasUserKnowledge)
					{
						for (int k = 0; k < cpost->precondition_beliefs[0].itemsAmount; k++)
						{
							Implication *imp = &cpost->precondition_beliefs[0].array[k];
							if (imp->isUserKnowledge)
							{
								Term subject = term_extract_subterm(&imp->term, 1);
								if (variable_unify(&subject, &event->term).success)
								{
									ASSERT(narsese_copula_equals(imp->term.atoms[0], '$'),
									       "Not a valid implication term!");
									Term precondition_with_op = term_extract_subterm(&imp->term, 1);
									Term precondition = narsese_get_precondition_without_op(&precondition_with_op);
									Substitution subs = variable_unify(&precondition, &event->term);
									if (subs.success)
									{
										Implication updated_imp = *imp;
										bool success;
										updated_imp.term = variable_apply_substitute(updated_imp.term, subs, &success);
										if (success)
										{
											Event predicted = inference_belief_deduction(event, &updated_imp);
											memory_add_event(&predicted,
											                 currentTime,
											                 priority * truth_expectation(imp->truth) *
												                 truth_expectation(predicted.truth),
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
memory_add_event(Event *event, long currentTime, double priority, double occurrenceTimeOffset, bool input, bool derived,
                 bool readded, bool revised, bool predicted)
{
	if (readded) //readded events get durability applied, they already got complexity-penalized
	{
		priority *= EVENT_DURABILITY_ON_USAGE;
	}
	else if (!revised &&
		!input) //derivations get penalized by complexity as well, but revised ones not as they already come from an input or derivation
	{
		double complexity = term_complexity(&event->term);
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
				fifo_add(event, &g_beliefEvents); //not revised yet
			}
		}
	}
	bool isImplication = narsese_copula_equals(event->term.atoms[0], '$');
	if (!readded && !isImplication) //print new tasks
	{
		memory_print_added_event(event, priority, input, derived, revised, true);
	}
	if (event->type == EVENT_TYPE_BELIEF)
	{
		if (!readded)
		{
			memory_process_new_belief_event(event, currentTime, priority, occurrenceTimeOffset, input, predicted,
			                                isImplication);
			if (isImplication)
			{
				return;
			}
		}
		memory_add_cycling_event(event, priority, currentTime);
	}
	if (event->type == EVENT_TYPE_GOAL)
	{
		ASSERT(event->occurrenceTime != OCCURRENCE_ETERNAL, "Eternal goals are not supported");
		memory_add_cycling_event(event, priority, currentTime);
	}
	ASSERT(event->type == EVENT_TYPE_BELIEF || event->type == EVENT_TYPE_GOAL, "Errornous event type");
}

void
memory_add_input_event(Event *event, double occurrenceTimeOffset, long currentTime)
{
	memory_add_event(event, currentTime, 1, occurrenceTimeOffset, true, false, false, false, false);
}

bool
memory_implication_valid(Implication *imp)
{
	return imp->sourceConceptId == ((Concept *) imp->sourceConcept)->id;
}
