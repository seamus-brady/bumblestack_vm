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

#include "nars_cycle.h"

static long conceptProcessID = 0; //avoids duplicate concept processing

#define RELATED_CONCEPTS_FOREACH(TERM, CONCEPT, BODY) \
    for(int _i_=0; _i_<UNIFICATION_DEPTH; _i_++) \
    { \
        ConceptChainElement chain_extended = { .c =   \
        memory_find_concept_by_term(TERM), .next = inverted_atom_index_get_concept_chain((TERM)->atoms[_i_]) }; \
        ConceptChainElement* chain = &chain_extended; \
        while(chain != NULL) \
        { \
            Concept *CONCEPT = chain->c; \
            chain = chain->next; \
            if(CONCEPT != NULL && CONCEPT->processID != conceptProcessID) \
            { \
                CONCEPT->processID = conceptProcessID; \
                BODY \
            } \
        } \
    }

//doing inference within the matched concept, returning whether decisionMaking should continue
static Decision
cycle_activate_sensorimotor_concept(Concept *c, Event *e, long currentTime)
{
	Decision decision = {0};
	if (e->truth.confidence > MIN_CONFIDENCE)
	{
		c->usage = Usage_use(c->usage, currentTime, false);
		//add event as spike to the concept:
		if (e->type == EVENT_TYPE_BELIEF)
		{
			c->belief_spike = *e;
		}
		else
		{
			//pass spike if the concept doesn't have a satisfying motor command
			decision = Decision_Suggest(c, e, currentTime);
		}
	}
	return decision;
}

//Process an event, by creating a concept, or activating an existing
static Decision
cycle_process_sensorimotor_event(Event *e, long currentTime)
{
	Decision best_decision = {0};
	//add a new concept for e if not yet existing
	memory_conceptualise(&e->term, currentTime);
	e->processed = true;
	//determine the concept it is related to
	bool e_hasVariable = Variable_hasVariable(&e->term, true, true, true);
	conceptProcessID++; //process the to e related g_concepts
	RELATED_CONCEPTS_FOREACH(&e->term, c,
	                         {
		                         Event ecp = *e;
		                         if (!e_hasVariable)  //concept matched to the event which doesn't have variables
		                         {
			                         Substitution subs = Variable_Unify(&c->term, &e->term); //concept with variables,
			                         if (subs.success)
			                         {
				                         ecp.term = e->term;
				                         Decision decision = cycle_activate_sensorimotor_concept(c, &ecp, currentTime);
				                         if (decision.execute && decision.desire >= best_decision.desire &&
					                         (!best_decision.specialized || decision.specialized))
				                         {
					                         best_decision = decision;
				                         }
			                         }
		                         }
		                         else
		                         {
			                         Substitution subs = Variable_Unify(&e->term,
			                                                            &c->term); //event with variable matched to concept
			                         if (subs.success)
			                         {
				                         bool success;
				                         ecp.term = Variable_ApplySubstitute(e->term, subs, &success);
				                         if (success)
				                         {
					                         Decision decision = cycle_activate_sensorimotor_concept(c, &ecp,
					                                                                                 currentTime);
					                         if (decision.execute && decision.desire >= best_decision.desire &&
						                         (!best_decision.specialized || decision.specialized))
					                         {
						                         best_decision = decision;
					                         }
				                         }
			                         }
		                         }
	                         })
	return best_decision;
}

void
cycle_pop_events(Event *selectionArray, double *selectionPriority, int *selectedCnt, PriorityQueue *queue, int cnt)
{
	*selectedCnt = 0;
	for (int i = 0; i < cnt; i++)
	{
		Event *e;
		double priority = 0;
		if (!PriorityQueue_PopMax(queue, (void **) &e, &priority))
		{
			ASSERT(queue->itemsAmount == 0, "No item was popped, only acceptable reason is when it's empty");
			IS_SYSTEM_IN_DEBUG_MODE(puts("PriorityQueue seems to have no events as selecting event failed.");)
			break;
		}
		selectionPriority[*selectedCnt] = priority;
		selectionArray[*selectedCnt] = *e; //needs to be copied because will be added in a batch
		(*selectedCnt)++; //that while processing, would make recycled pointers invalid to use
	}
}

//Derive a subgoal from a sequence goal
//{Event (a &/ b)!, Event a.} |- Event b! Truth_Deduction
//if Truth_Expectation(a) >= ANTICIPATION_THRESHOLD else
//{Event (a &/ b)!} |- Event a! Truth_StructuralDeduction
bool
cycle_goal_sequence_decomposition(Event *selectedGoal, double selectedGoalPriority)
{
	//1. Extract potential subgoals
	if (!narsese_copula_equals(selectedGoal->term.atoms[0], '+')) //left-nested sequence
	{
		return false;
	}
	Term componentGoalsTerm[MAX_SEQUENCE_LEN + 1] = {0};
	Term cur_seq = selectedGoal->term;
	int i = 0;
	for (; narsese_copula_equals(cur_seq.atoms[0], '+'); i++)
	{
		ASSERT(i <= MAX_SEQUENCE_LEN,
		       "The sequence was longer than MAX_SEQUENCE_LEN, change your input or increase the parameter!");
		componentGoalsTerm[i] = Term_ExtractSubterm(&cur_seq, 2);
		cur_seq = Term_ExtractSubterm(&cur_seq, 1);
	}
	componentGoalsTerm[i] = cur_seq; //the last element at this point
	//2. Find first subgoal which isn't fulfilled
	int lastComponentOccurrenceTime = -1;
	Event newGoal = inference_event_update(selectedGoal, g_currentTime);
	int j = i;
	for (; j >= 0; j--)
	{
		Term *componentGoal = &componentGoalsTerm[j];
		Substitution best_subs = {0};
		Concept *best_c = NULL;
		double best_exp = 0.0;
		//the concept with belief event of highest truth exp
		conceptProcessID++;
		RELATED_CONCEPTS_FOREACH(componentGoal, c,
		                         {
			                         if (!Variable_hasVariable(&c->term, true, true,
			                                                   true))  //concept matched to the event which doesn't have variables
			                         {
				                         Substitution subs = Variable_Unify(componentGoal,
				                                                            &c->term); //event with variable matched to concept
				                         if (subs.success)
				                         {
					                         bool success = true;
					                         if (c->belief_spike.type != EVENT_TYPE_DELETED)
					                         {
						                         //check whether the temporal order is violated
						                         if (c->belief_spike.occurrenceTime < lastComponentOccurrenceTime)
						                         {
							                         continue;
						                         }
						                         //check whether belief is too weak (not recent enough or not true enough)
						                         if (Truth_Expectation(Truth_Projection(c->belief_spike.truth,
						                                                                c->belief_spike.occurrenceTime,
						                                                                g_currentTime)) <
							                         CONDITION_THRESHOLD)
						                         {
							                         continue;
						                         }
						                         //check whether the substitution works for the subgoals coming after it
						                         for (int u = j - 1; u >= 0; u--)
						                         {
							                         bool goalsubs_success;
							                         Variable_ApplySubstitute(componentGoalsTerm[u], subs,
							                                                  &goalsubs_success);
							                         if (!goalsubs_success)
							                         {
								                         success = false;
								                         break;
							                         }
						                         }
						                         //Use this specific concept for subgoaling if it has the strongest belief event
						                         if (success)
						                         {
							                         double expectation = Truth_Expectation(
								                         Truth_Projection(c->belief_spike.truth,
								                                          c->belief_spike.occurrenceTime,
								                                          g_currentTime));
							                         if (expectation > best_exp)
							                         {
								                         best_exp = expectation;
								                         best_c = c;
								                         best_subs = subs;
							                         }
						                         }
					                         }
				                         }
			                         }
			                         //no need to search another concept, as it didn't have a var so the concept we just iterated is the only one
			                         if (!Variable_hasVariable(componentGoal, true, true, true))
			                         {
				                         goto DONE_CONCEPT_ITERATING;
			                         }
		                         })
		DONE_CONCEPT_ITERATING:
		//no corresponding belief
		if (best_c == NULL)
		{
			break;
		}
		//all components fulfilled? Then nothing to do
		if (j == 0)
		{
			return true;
		}
		//Apply substitution implied by the event satisfying the current subgoal to the next subgoals
		for (int u = j - 1; u >= 0; u--)
		{
			bool goalsubs_success;
			componentGoalsTerm[u] = Variable_ApplySubstitute(componentGoalsTerm[u], best_subs, &goalsubs_success);
			ASSERT(goalsubs_success, "cycle_goal_sequence_decomposition: The subsitution succeeded before but not now!");
		}
		//build component subgoal according to {(a, b)!, a} |- b! Truth_Deduction
		lastComponentOccurrenceTime = best_c->belief_spike.occurrenceTime;
		newGoal = Inference_GoalSequenceDeduction(&newGoal, &best_c->belief_spike, g_currentTime);
		newGoal.term = componentGoalsTerm[j - 1];
	}
	if (j == i) //we derive first component according to {(a,b)!} |- a! Truth_StructuralDeduction
	{
		newGoal.term = componentGoalsTerm[i];
		newGoal.truth = Truth_StructuralDeduction(newGoal.truth, newGoal.truth);
	}
	memory_add_event(&newGoal, g_currentTime, selectedGoalPriority * Truth_Expectation(newGoal.truth), 0, false, true,
	                 false, false, false);
	return true;
}

//Propagate subgoals, leading to decisions
static void
cycle_process_input_goal_events(long currentTime)
{
	Decision best_decision = {0};
	//process selected goals
	for (int i = 0; i < g_goalsSelectedCnt; i++)
	{
		Event *goal = &g_selectedGoals[i];
		IS_SYSTEM_IN_DEBUG_MODE(fputs("Selected goal: ", stdout); narsese_print_term(&goal->term); puts("");)
		//if goal is a sequence, overwrite with first deduced non-fulfilled element
		if (cycle_goal_sequence_decomposition(goal,
		                                      g_selectedGoalsPriority[i])) //the goal was a sequence which leaded to a subgoal derivation
		{
			continue;
		}
		Decision decision = cycle_process_sensorimotor_event(goal, currentTime);
		if (decision.execute && decision.desire > best_decision.desire &&
			(!best_decision.specialized || decision.specialized))
		{
			best_decision = decision;
		}
	}
	if (best_decision.execute && best_decision.operationID > 0)
	{
		//reset cycling goal events after execution to avoid "residue actions"
		PriorityQueue_INIT(&g_cyclingGoalEvents, g_cyclingGoalEvents.items, g_cyclingGoalEvents.maxElements);
		//also don't re-add the selected goal:
		g_goalsSelectedCnt = 0;
		//execute decision
		decision_execute(&best_decision);
	}
	//pass goal spikes on to the next
	for (int i = 0; i < g_goalsSelectedCnt && !best_decision.execute; i++)
	{
		Event *goal = &g_selectedGoals[i];
		conceptProcessID++; //process subgoaling for the related g_concepts for each selected goal
		RELATED_CONCEPTS_FOREACH(&goal->term, c,
		                         {
			                         if (Variable_Unify(&c->term, &goal->term).success)
			                         {
				                         bool revised;
				                         c->goal_spike =
					                         inference_revision_and_choice(&c->goal_spike, goal, currentTime,
					                                                       &revised);
				                         for (int opi = 0; opi <= OPERATIONS_MAX; opi++)
				                         {
					                         for (int j = 0; j < c->precondition_beliefs[opi].itemsAmount; j++)
					                         {
						                         Implication *imp = &c->precondition_beliefs[opi].array[j];
						                         if (!memory_implication_valid(imp))
						                         {
							                         Table_Remove(&c->precondition_beliefs[opi], j);
							                         j--;
							                         continue;
						                         }
						                         Term postcondition = Term_ExtractSubterm(&imp->term, 2);
						                         Substitution subs = Variable_Unify(&postcondition,
						                                                            &c->goal_spike.term);
						                         Implication updated_imp = *imp;
						                         bool success;
						                         updated_imp.term = Variable_ApplySubstitute(updated_imp.term, subs,
						                                                                     &success);
						                         if (success)
						                         {
							                         Event newGoal = inference_goal_deduction(&c->goal_spike,
							                                                                  &updated_imp);
							                         Event newGoalUpdated = inference_event_update(&newGoal,
							                                                                       currentTime);
							                         IS_SYSTEM_IN_DEBUG_MODE(fputs("derived goal ", stdout);
							                         narsese_print_term(&newGoalUpdated.term);
							                         puts(""); )
							                         memory_add_event(&newGoalUpdated,
							                                          currentTime,
							                                          g_selectedGoalsPriority[i] *
								                                          Truth_Expectation(newGoalUpdated.truth),
							                                          0,
							                                          false,
							                                          true,
							                                          false,
							                                          false,
							                                          false);
						                         }
					                         }
				                         }
			                         }
		                         })
	}
}

//Reinforce link between concept a and b (creating it if non-existent)
static void
cycle_reinforce_link(Event *a, Event *b)
{
	if (a->type != EVENT_TYPE_BELIEF || b->type != EVENT_TYPE_BELIEF)
	{
		return;
	}
	Term a_term_nop = narsese_get_precondition_without_op(&a->term);
	Concept *A = memory_find_concept_by_term(&a_term_nop);
	Concept *B = memory_find_concept_by_term(&b->term);
	if (A != NULL && B != NULL && A != B)
	{
		//temporal induction
		if (!Stamp_checkOverlap(&a->stamp, &b->stamp))
		{
			bool success;
			Implication precondition_implication = inference_belief_induction(a, b, &success);
			if (success)
			{
				precondition_implication.sourceConcept = A;
				precondition_implication.sourceConceptId = A->id;
				if (precondition_implication.truth.confidence >= MIN_CONFIDENCE)
				{
					//extensional var intro:
					bool success;
					Term general_implication_term_ext = IntroduceImplicationVariables(precondition_implication.term,
					                                                                  &success, true);
					if (success && Variable_hasVariable(&general_implication_term_ext, true, true, false))
					{
						nal_derived_event(general_implication_term_ext,
						                  OCCURRENCE_ETERNAL,
						                  precondition_implication.truth,
						                  precondition_implication.stamp,
						                  g_currentTime,
						                  1,
						                  1,
						                  precondition_implication.occurrenceTimeOffset,
						                  NULL,
						                  0);
					}
					//intensional var intro:
					bool success2;
					Term general_implication_term_int = IntroduceImplicationVariables(precondition_implication.term,
					                                                                  &success2, false);
					if (success2 && Variable_hasVariable(&general_implication_term_int, true, true, false))
					{
						nal_derived_event(general_implication_term_int,
						                  OCCURRENCE_ETERNAL,
						                  precondition_implication.truth,
						                  precondition_implication.stamp,
						                  g_currentTime,
						                  1,
						                  1,
						                  precondition_implication.occurrenceTimeOffset,
						                  NULL,
						                  0);
					}
					//specific implication
					nal_derived_event(precondition_implication.term, OCCURRENCE_ETERNAL, precondition_implication.truth,
					                  precondition_implication.stamp, g_currentTime, 1, 1,
					                  precondition_implication.occurrenceTimeOffset, NULL, 0);
				}
			}
		}
	}
}

void
cycle_push_events(long currentTime)
{
	for (int i = 0; i < g_beliefsSelectedCnt; i++)
	{
		memory_add_event(&g_selectedBeliefs[i], currentTime, g_selectedBeliefsPriority[i], 0, false, false, true, false,
		                 false);
	}
	for (int i = 0; i < g_goalsSelectedCnt; i++)
	{
		memory_add_event(&g_selectedGoals[i],
		                 currentTime,
		                 g_selectedGoalsPriority[i],
		                 0,
		                 false,
		                 false,
		                 true,
		                 false,
		                 false);
	}
}

void
cycle_process_input_belief_events(long currentTime)
{
	//1. process newest event
	if (g_beliefEvents.itemsAmount > 0)
	{
		//form g_concepts for the sequences of different length
		for (int len = MAX_SEQUENCE_LEN - 1; len >= 0; len--)
		{
			Event *toProcess = fifo_get_newest_sequence(&g_beliefEvents, len);
			if (toProcess != NULL && !toProcess->processed && toProcess->type != EVENT_TYPE_DELETED)
			{
				ASSERT(toProcess->type == EVENT_TYPE_BELIEF, "A different event type made it into belief events!");
				cycle_process_sensorimotor_event(toProcess, currentTime);
				Event postcondition = *toProcess;
				//Mine for <(&/,precondition,operation) =/> postcondition> patterns in the FIFO:
				if (len == 0) //postcondition always len1
				{
					int op_id = narsese_get_operation_id(&postcondition.term);
					decision_anticipate(op_id, currentTime); //collection of negative evidence, new way
					for (int k = 1; k < g_beliefEvents.itemsAmount; k++)
					{
						for (int len2 = 0; len2 < MAX_SEQUENCE_LEN; len2++)
						{
							Event *precondition = fifo_get_kth_newest_sequence(&g_beliefEvents, k, len2);
							if (len2 > 0)
							{
								Event *potential_op = fifo_get_kth_newest_sequence(&g_beliefEvents, k + len2, 0);
								if (potential_op != NULL && potential_op->type != EVENT_TYPE_DELETED &&
									narsese_is_operation(&potential_op->term))
								{
									break;
								}
							}
							if (precondition != NULL && precondition->type != EVENT_TYPE_DELETED)
							{
								cycle_reinforce_link(precondition, &postcondition);
							}
						}
					}
				}
			}
		}
	}
}

void
cycle_inference(long currentTime)
{
	//Inferences
	for (int i = 0; i < g_beliefsSelectedCnt; i++)
	{
		conceptProcessID++; //process the related belief g_concepts
		long countConceptsMatched = 0;
		for (;;)
		{
			long countConceptsMatchedNew = 0;
			//Adjust dynamic firing threshold: (proportional "self"-control)
			double conceptPriorityThresholdCurrent = g_conceptPriorityThreshold;
			long countConceptsMatchedAverage = Stats_countConceptsMatchedTotal / currentTime;
			double set_point = BELIEF_CONCEPT_MATCH_TARGET;
			double process_value = countConceptsMatchedAverage;
			double error = process_value - set_point;
			double increment = error * CONCEPT_THRESHOLD_ADAPTATION;
			g_conceptPriorityThreshold = MIN(1.0, MAX(0.0, g_conceptPriorityThreshold + increment));
			IS_SYSTEM_IN_DEBUG_MODE(printf("g_conceptPriorityThreshold=(%f)\n", g_conceptPriorityThreshold);)
			Event *e = &g_selectedBeliefs[i];
			double priority = g_selectedBeliefsPriority[i];
			Term dummy_term = {0};
			Truth dummy_truth = {0};
			RuleTableApply(e->term, dummy_term, e->truth, dummy_truth, e->occurrenceTime, 0, e->stamp, currentTime,
			               priority, 1, false, NULL, 0);
			RELATED_CONCEPTS_FOREACH(&e->term, c,
			                         {
				                         long validation_cid =
					                         c->id; //allows for lockfree rule table application (only adding to memory is locked)
				                         if (c->priority < conceptPriorityThresholdCurrent)
				                         {
					                         continue;
				                         }
				                         countConceptsMatchedNew++;
				                         countConceptsMatched++;
				                         Stats_countConceptsMatchedTotal++;
				                         if (c->belief.type != EVENT_TYPE_DELETED &&
					                         countConceptsMatched <= BELIEF_CONCEPT_MATCH_TARGET)
				                         {
					                         //use eternal belief as belief
					                         Event *belief = &c->belief;
					                         Event future_belief = c->predicted_belief;
					                         //but if there is a predicted one in the event's window, use this one
					                         if (e->occurrenceTime != OCCURRENCE_ETERNAL &&
						                         future_belief.type != EVENT_TYPE_DELETED &&
						                         labs(e->occurrenceTime - future_belief.occurrenceTime) <
							                         EVENT_BELIEF_DISTANCE) //take event as belief if it's stronger
					                         {
						                         future_belief.truth = Truth_Projection(future_belief.truth,
						                                                                future_belief.occurrenceTime,
						                                                                e->occurrenceTime);
						                         future_belief.occurrenceTime = e->occurrenceTime;
						                         belief = &future_belief;
					                         }
					                         //unless there is an actual belief which falls into the event's window
					                         Event project_belief = c->belief_spike;
					                         if (e->occurrenceTime != OCCURRENCE_ETERNAL &&
						                         project_belief.type != EVENT_TYPE_DELETED &&
						                         labs(e->occurrenceTime - project_belief.occurrenceTime) <
							                         EVENT_BELIEF_DISTANCE) //take event as belief if it's stronger
					                         {
						                         project_belief.truth = Truth_Projection(project_belief.truth,
						                                                                 project_belief.occurrenceTime,
						                                                                 e->occurrenceTime);
						                         project_belief.occurrenceTime = e->occurrenceTime;
						                         belief = &project_belief;
					                         }
					                         //Check for overlap and apply inference rules
					                         if (!Stamp_checkOverlap(&e->stamp, &belief->stamp))
					                         {
						                         c->usage = Usage_use(c->usage, currentTime, false);
						                         Stamp stamp = Stamp_make(&e->stamp, &belief->stamp);
						                         if (PRINT_CONTROL_INFO)
						                         {
							                         fputs("Apply rule table on ", stdout);
							                         narsese_print_term(&e->term);
							                         printf(" priority=(%f)\n", priority);
							                         fputs(" and ", stdout);
							                         narsese_print_term(&c->term);
							                         puts("");
						                         }
						                         long occurrenceTimeDistance = 0;
						                         if (belief->occurrenceTime != OCCURRENCE_ETERNAL &&
							                         e->occurrenceTime != OCCURRENCE_ETERNAL)
						                         {
							                         occurrenceTimeDistance = labs(
								                         belief->occurrenceTime - e->occurrenceTime);
						                         }
						                         RuleTableApply(e->term, c->term, e->truth, belief->truth,
						                                        e->occurrenceTime, occurrenceTimeDistance, stamp,
						                                        currentTime, priority, c->priority, true, c,
						                                        validation_cid);
					                         }
				                         }
			                         })
			if (countConceptsMatched > Stats_countConceptsMatchedMax)
			{
				Stats_countConceptsMatchedMax = countConceptsMatched;
			}
			if (countConceptsMatched >= BELIEF_CONCEPT_MATCH_TARGET || countConceptsMatchedNew == 0)
			{
				break;
			}
		}
	}
}

void
cycle_prediction(long currentTime)
{
	for (int h = 0; h < g_beliefsSelectedCnt; h++)
	{
		Event *e = &g_selectedBeliefs[h];
		double parentpriority = g_selectedBeliefsPriority[h];
		for (int j = 0; j < g_concepts.itemsAmount; j++)
		{
			Concept *c = g_concepts.items[j].address;
			if (c->priority < g_conceptPriorityThreshold)
			{
				continue;
			}
			for (int k = 0; k < c->precondition_beliefs[0].itemsAmount; k++)
			{
				if (!memory_implication_valid(&c->precondition_beliefs[0].array[k]))
				{
					Table_Remove(&c->precondition_beliefs[0], k--);
					continue;
				}
				Implication *imp = &c->precondition_beliefs[0].array[k];
				Term precondition = Term_ExtractSubterm(&imp->term, 1);
				Substitution subs = Variable_Unify(&precondition, &e->term);
				if (subs.success)
				{
					ASSERT(narsese_copula_equals(imp->term.atoms[0], '$'), "Not a valid implication term!");
					Concept *c_pre = memory_find_concept_by_term(&precondition);
					if (c_pre != NULL)
					{
						Substitution subs = Variable_Unify(&precondition, &e->term);
						Implication updated_imp = *imp;
						bool success;
						updated_imp.term = Variable_ApplySubstitute(updated_imp.term, subs, &success);
						if (success)
						{
							Event predicted = inference_belief_deduction(e, &updated_imp);
							memory_add_event(&predicted, currentTime,
							                 parentpriority * Truth_Expectation(predicted.truth), 0, false, true,
							                 false, false, true);
						}
					}
				}
			}
		}
	}
}

void
cycle_relative_forgetting(long currentTime)
{
	//Apply event forgetting:
	for (int i = 0; i < g_cyclingBeliefEvents.itemsAmount; i++)
	{
		g_cyclingBeliefEvents.items[i].priority *= EVENT_DURABILITY;
	}
	for (int i = 0; i < g_cyclingGoalEvents.itemsAmount; i++)
	{
		g_cyclingGoalEvents.items[i].priority *= EVENT_DURABILITY;
	}
	//Apply concept forgetting:
	for (int i = 0; i < g_concepts.itemsAmount; i++)
	{
		Concept *c = g_concepts.items[i].address;
		c->priority *= CONCEPT_DURABILITY;
		g_concepts.items[i].priority = Usage_usefulness(c->usage,
		                                                currentTime); //how concept memory is sorted by, by concept usefulness
	}
	//BEGIN SPECIAL HANDLING FOR USER KNOWLEDGE
	if (g_ontologyHandling)
	{
		//BEGIN SPECIAL HANDLING FOR USER KNOWLEDGE
		for (int i = 0; i < g_concepts.itemsAmount; i++)
		{
			Concept *c = g_concepts.items[i].address;
			if (c->hasUserKnowledge)
			{
				c->usage = Usage_use(c->usage, currentTime, false); //user implication won't be forgotten
			}
		}
	}
	//END SPECIAL HANDLING FOR USER KNOWLEDGE
	//Re-sort queues
	PriorityQueue_Rebuild(&g_concepts);
	PriorityQueue_Rebuild(&g_cyclingBeliefEvents);
	PriorityQueue_Rebuild(&g_cyclingGoalEvents);
}

void
cycle_perform(long currentTime)
{
	//1. Retrieve BELIEF/GOAL_EVENT_SELECTIONS events from cyclings events priority queue (which includes both input and derivations)
	cycle_pop_events(g_selectedGoals, g_selectedGoalsPriority, &g_goalsSelectedCnt, &g_cyclingGoalEvents,
	                 GOAL_EVENT_SELECTIONS);
	cycle_pop_events(g_selectedBeliefs, g_selectedBeliefsPriority, &g_beliefsSelectedCnt, &g_cyclingBeliefEvents,
	                 BELIEF_EVENT_SELECTIONS);
	//2. Process incoming belief events from FIFO, building implications utilizing input sequences
	cycle_process_input_belief_events(currentTime);
	//3. Process incoming goal events, propagating subgoals according to implications, triggering decisions when above decision threshold
	cycle_process_input_goal_events(currentTime);
	//4. Perform inference between in 1. retrieved events and semantically/temporally related, high-priority g_concepts to derive and process new events
	cycle_inference(currentTime);
	cycle_prediction(currentTime);
	//5. Apply relative forgetting for g_concepts according to CONCEPT_DURABILITY and events according to BELIEF_EVENT_DURABILITY
	cycle_relative_forgetting(currentTime);
	//6. Push in 1. selected events back to the queue as well, applying relative forgetting based on BELIEF_EVENT_DURABILITY_ON_USAGE
	cycle_push_events(currentTime);
}
