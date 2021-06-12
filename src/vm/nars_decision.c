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

#include "nars_decision.h"

double CONDITION_THRESHOLD = CONDITION_THRESHOLD_INITIAL;
double DECISION_THRESHOLD = DECISION_THRESHOLD_INITIAL;
double ANTICIPATION_THRESHOLD = ANTICIPATION_THRESHOLD_INITIAL;
double ANTICIPATION_CONFIDENCE = ANTICIPATION_CONFIDENCE_INITIAL;
double MOTOR_BABBLING_CHANCE = MOTOR_BABBLING_CHANCE_INITIAL;
int BABBLING_OPS = OPERATIONS_MAX;

int g_stampID = -1;

//Inject action event after execution or babbling
void
decision_execute(Decision *decision)
{
	ASSERT(decision->operationID > 0, "Operation 0 is reserved for no action");
	decision->op = g_operations[decision->operationID - 1];
	Term feedback = decision->op.term; //atomic operation / operator
	//and add operator feedback
	if (decision->arguments.atoms[0] > 0) //operation with args
	{
		Term operation = {0};
		operation.atoms[0] = narsese_atomic_term_index(":"); //<args --> ^op>
		if (!Term_OverrideSubterm(&operation, 1, &decision->arguments) ||
			!Term_OverrideSubterm(&operation, 2, &decision->op.term))
		{
			return;
		}
		feedback = operation;
	}
	(*decision->op.action)(decision->arguments);
	NAR_AddInputBelief(feedback);
}

//"reflexes" to try different g_operations, especially important in the beginning
static Decision
decision_motor_babbling()
{
	Decision decision = (Decision) {0};
	int n_ops = 0;
	for (int i = 0; i < OPERATIONS_MAX && g_operations[i].action != 0; i++)
	{
		n_ops = i + 1;
	}
	if (n_ops > 0)
	{
		decision.operationID = 1 + (globals_next_rand() % (MIN(BABBLING_OPS, n_ops)));
		IS_SYSTEM_IN_DEBUG_MODE (
			printf(" NAR BABBLE %d\n", decision.operationID);
		)
		decision.execute = true;
		decision.desire = 1.0;
	}
	return decision;
}

static Decision
decision_consider_implication(long currentTime, Event *goal, int considered_opi, Implication *imp)
{
	Decision decision = {0};
	IS_SYSTEM_IN_DEBUG_MODE
	(
		printf("Considered implication with truth: truth=(frequency=%f, confidence=%f) ",
		       imp->truth.frequency,
		       imp->truth.confidence);
		narsese_print_term(&imp->term);
		puts("");
	)
	//now look at how much the precondition is fulfilled
	Concept *prec = imp->sourceConcept;
	Event *precondition = &prec->belief_spike; //a. :|:
	if (precondition != NULL)
	{
		Event ContextualOperation = inference_goal_deduction(goal, imp); //(&/,a,op())! :\:
		double operationGoalTruthExpectation = Truth_Expectation(
			Inference_GoalSequenceDeduction(&ContextualOperation, precondition, currentTime).truth); //op()! :|:
		IS_SYSTEM_IN_DEBUG_MODE
		(
			printf("Considered precondition with desire: operationGoalTruthExpectation=(%f) ",
			       operationGoalTruthExpectation);
			narsese_print_term(&prec->term);
			fputs("\nConsidered precondition with truth: ", stdout);
			Truth_Print(&precondition->truth);
			fputs("Considered goal with truth: ", stdout);
			Truth_Print(&goal->truth);
			fputs("Considered implication with truth: ", stdout);
			Truth_Print(&imp->truth);
			printf("Considered at system time occurrenceTime=(%ld)\n", precondition->occurrenceTime);
			narsese_print_term(&precondition->term); puts("");
		)
		//<(precon &/ <args --> ^op>) =/> postcon>. -> [$ , postcon precon : _ _ _ _ args ^op
		Term operation = Term_ExtractSubterm(&imp->term, 4); //^op or [: args ^op]
		if (!narsese_is_operator(
			operation.atoms[0])) //it is an operation with args, not just an atomic operator, so remember the args
		{
			ASSERT(narsese_is_operator(operation.atoms[2]),
			       "If it's not atomic, it needs to be an operation with args here");
			Term arguments = Term_ExtractSubterm(&imp->term, 9); //[* ' ARG g_Self]
			if (arguments.atoms[3] != g_Self) //either wasn't g_Self or var didn't resolve to g_Self
			{
				return decision;
			}
			decision.arguments = arguments;

		}
		decision.reason = precondition;
		decision.operationID = considered_opi;
		decision.desire = operationGoalTruthExpectation;
	}
	return decision;
}

Decision
decision_best_candidate(Concept *goalconcept, Event *goal, long currentTime)
{
	Decision decision = {0};
	Implication bestImp = {0};
	long bestComplexity = COMPOUND_TERM_SIZE_MAX + 1;
	Decision decisionGeneral = {0};
	Implication bestImpGeneral = {0};
	long bestComplexityGeneral = COMPOUND_TERM_SIZE_MAX + 1;
	Substitution subs = Variable_Unify(&goalconcept->term, &goal->term);
	if (subs.success)
	{
		for (int opi = 1; opi <= OPERATIONS_MAX && g_operations[opi - 1].action != 0; opi++)
		{
			for (int j = 0; j < goalconcept->precondition_beliefs[opi].itemsAmount; j++)
			{
				if (!memory_implication_valid(&goalconcept->precondition_beliefs[opi].array[j]))
				{
					Table_Remove(&goalconcept->precondition_beliefs[opi], j--);
					continue;
				}
				Implication imp = goalconcept->precondition_beliefs[opi].array[j];
				bool impHasVariable = Variable_hasVariable(&imp.term, true, true, true);
				bool success;
				imp.term = Variable_ApplySubstitute(imp.term, subs, &success);
				if (success)
				{
					ASSERT(narsese_copula_equals(imp.term.atoms[0], '$'), "This should be an implication!");
					Term left_side_with_op = Term_ExtractSubterm(&imp.term, 1);
					Term left_side = narsese_get_precondition_without_op(
						&left_side_with_op); //might be something like <#1 --> a>
					for (int cmatch_k = 0; cmatch_k < g_concepts.itemsAmount; cmatch_k++)
					{
						Concept *cmatch = g_concepts.items[cmatch_k].address;
						if (!Variable_hasVariable(&cmatch->term, true, true, true))
						{
							Substitution subs2 = Variable_Unify(&left_side, &cmatch->term);
							if (subs2.success)
							{
								Implication specific_imp = imp; //can only be completely specific
								bool success;
								specific_imp.term = Variable_ApplySubstitute(specific_imp.term, subs2, &success);
								if (success && !Variable_hasVariable(&specific_imp.term, true, true, true))
								{
									specific_imp.sourceConcept = cmatch;
									specific_imp.sourceConceptId = cmatch->id;
									Decision considered = decision_consider_implication(currentTime, goal, opi,
									                                                    &specific_imp);
									int specific_imp_complexity = Term_Complexity(&specific_imp.term);
									if (impHasVariable)
									{
										if (considered.desire > decisionGeneral.desire ||
											(considered.desire == decisionGeneral.desire &&
												specific_imp_complexity < bestComplexityGeneral))
										{
											decisionGeneral = considered;
											bestComplexityGeneral = specific_imp_complexity;
											bestImpGeneral = imp;
										}
									}
									else
									{
										if (considered.desire > decision.desire ||
											(considered.desire == decision.desire &&
												specific_imp_complexity < bestComplexity))
										{
											decision = considered;
											decision.specialized = true;
											bestComplexity = specific_imp_complexity;
											bestImp = imp;
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	//use general solution only if the specific solution doesn't exceed the threshold
	if (decisionGeneral.desire > decision.desire && decision.desire < DECISION_THRESHOLD)
	{
		decision = decisionGeneral;
		bestImp = bestImpGeneral;
	}
	if (decision.desire < DECISION_THRESHOLD)
	{
		return (Decision) {0};
	}
	//set execute and return execution
	printf("Decision expectation=(%f) implication: ", decision.desire);
	narsese_print_term(&bestImp.term);
	printf(". truth=(frequency=%f confidence=%f) occurrenceTimeOffset=(%f)",
	       bestImp.truth.frequency,
	       bestImp.truth.confidence,
	       bestImp.occurrenceTimeOffset);
	fputs(" precondition: ", stdout);
	narsese_print_term(&decision.reason->term);
	fputs(". :|: ", stdout);
	printf("truth=(frequency=%f confidence=%f)", decision.reason->truth.frequency, decision.reason->truth.confidence);
	printf(" occurrenceTime=(%ld)\n", decision.reason->occurrenceTime);
	decision.execute = true;
	return decision;
}

void
decision_anticipate(int operationID, long currentTime)
{
	ASSERT(operationID >= 0 && operationID <= OPERATIONS_MAX, "Wrong operation id, did you inject an event manually?");
	for (int j = 0; j < g_concepts.itemsAmount; j++)
	{
		Concept *postc = g_concepts.items[j].address;
		for (int h = 0; h < postc->precondition_beliefs[operationID].itemsAmount; h++)
		{
			if (!memory_implication_valid(&postc->precondition_beliefs[operationID].array[h]))
			{
				Table_Remove(&postc->precondition_beliefs[operationID], h);
				h--;
				continue;
			}
			Implication imp = postc->precondition_beliefs[operationID].array[h]; //(&/,a,op) =/> b.
			Concept *current_prec = imp.sourceConcept;
			Event *precondition = &current_prec->belief_spike;
			if (precondition != NULL && precondition->type != EVENT_TYPE_DELETED)
			{
				ASSERT(precondition->occurrenceTime != OCCURRENCE_ETERNAL, "Precondition should not be eternal!");
				Event updated_precondition = inference_event_update(precondition, currentTime);
				Event op = {.type = EVENT_TYPE_BELIEF,
					.truth = (Truth) {.frequency = 1.0, .confidence = 0.9},
					.occurrenceTime = currentTime};
				bool success;
				Event seqop = inference_belief_intersection(&updated_precondition, &op, &success);
				if (success)
				{
					Event result = inference_belief_deduction(&seqop, &imp); //b. :/:
					if (Truth_Expectation(result.truth) > ANTICIPATION_THRESHOLD)
					{
						Implication negative_confirmation = imp;
						Truth TNew = {.frequency = 0.0, .confidence = ANTICIPATION_CONFIDENCE};
						Truth TPast = Truth_Projection(precondition->truth, 0, round(imp.occurrenceTimeOffset));
						negative_confirmation.truth = Truth_Eternalize(Truth_Induction(TNew, TPast));
						negative_confirmation.stamp = (Stamp) {.evidentialBase = {-g_stampID}};
						g_stampID--;
						ASSERT(negative_confirmation.truth.confidence >= 0.0 &&
							negative_confirmation.truth.confidence <= 1.0, "(666) confidence out of bounds");
						Implication *added = Table_AddAndRevise(&postc->precondition_beliefs[operationID],
						                                        &negative_confirmation);
						if (added != NULL)
						{
							added->sourceConcept = negative_confirmation.sourceConcept;
							added->sourceConceptId = negative_confirmation.sourceConceptId;
						}
						Substitution subs = Variable_Unify(&current_prec->term, &precondition->term);
						if (subs.success)
						{
							bool success2;
							result.term = Variable_ApplySubstitute(result.term, subs, &success2);
							if (success2)
							{
								Concept *c = memory_conceptualise(&result.term, currentTime);
								if (c != NULL)
								{
									c->usage = Usage_use(c->usage, currentTime, false);
									c->predicted_belief = result;
									Event eternal = result;
									eternal.truth = Truth_Eternalize(eternal.truth);
									eternal.occurrenceTime = OCCURRENCE_ETERNAL;
									c->belief = inference_revision_and_choice(&c->belief, &eternal, currentTime, NULL);
								}
							}
						}
					}
				}
			}
		}
	}
}

Decision
Decision_Suggest(Concept *postc, Event *goal, long currentTime)
{
	Decision babble_decision = {0};
	//try motor babbling with a certain chance
	if (globals_next_rand() < (int) (MOTOR_BABBLING_CHANCE * MY_RAND_MAX))
	{
		babble_decision = decision_motor_babbling();
	}
	//try matching op if didn't motor babble
	Decision decision_suggested = decision_best_candidate(postc, goal, currentTime);
	if (!babble_decision.execute || decision_suggested.desire > MOTOR_BABBLING_SUPPRESSION_THRESHOLD)
	{
		return decision_suggested;
	}
	return babble_decision;
}
