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

#include "nars_nar.h"
#include "lib_slog.h"
#include "nars_io.h"

long g_currentTime = 1;

static bool nar_initialized = false;

void
nar_init()
{
	ASSERT(pow(TRUTH_PROJECTION_DECAY_INITIAL, EVENT_BELIEF_DISTANCE) >= MIN_CONFIDENCE,
	       "Bad params, increase projection decay or decrease event belief distance!");
	memory_init(); //clear data structures
	event_init(); //reset g_base id counter
	narsese_init();
	g_currentTime = 1; //reset time
	nar_initialized = true;
}

void
nar_cycles(int cycles)
{
	ASSERT(nar_initialized, "NAR not g_narseseInitialized yet, call nar_init first!");
	for (int i = 0; i < cycles; i++)
	{
		IS_SYSTEM_IN_DEBUG_MODE(puts("\nStart of new inference cycle\n");)
		cycle_perform(g_currentTime);
		g_currentTime++;
	}
}

Event
nar_add_input(Term term, char type, Truth truth, bool eternal, double occurrenceTimeOffset, bool isUserKnowledge)
{
	ASSERT(nar_initialized, "NAR not g_narseseInitialized yet, call nar_init first!");
	Event ev = event_input_event(term, type, truth, g_currentTime);
	if (eternal)
	{
		ev.occurrenceTime = OCCURRENCE_ETERNAL;
		ev.isUserKnowledge = isUserKnowledge;
	}
	memory_add_input_event(&ev, occurrenceTimeOffset, g_currentTime);
	nar_cycles(1);
	return ev;
}

Event
nar_add_input_Belief(Term term)
{
	Event ret = nar_add_input(term, EVENT_TYPE_BELIEF, NAR_DEFAULT_TRUTH, false, 0, false);
	return ret;
}

Event
nar_add_input_goal(Term term)
{
	return nar_add_input(term, EVENT_TYPE_GOAL, NAR_DEFAULT_TRUTH, false, 0, false);
}

void
nar_add_operation(Term term, Action procedure, char *script_source)
{
	ASSERT(nar_initialized, "NAR g_narseseInitialized is false, call nar_init first!");
	char *term_name = g_narsese_atomNames[(int) term.atoms[0] - 1];
	ASSERT(term_name[0] == '^', "This atom does not belong to an operator!");
	ASSERT(narsese_operator_index(term_name) <= OPERATIONS_MAX, "Too many operators, increase OPERATIONS_MAX!");
	g_operations[narsese_operator_index(term_name) - 1] =
		(Operation) {.term = term, .term_string = term_name, .action = procedure, .script = script_source};
}

bool
nar_validate_input_narsese(char *narsese_sentence)
{
	Term term;
	Truth tv;
	char punctuation;
	int tense;
	bool isUserKnowledge;
	return narsese_check_sentence_is_valid(narsese_sentence, &punctuation, &tense, &isUserKnowledge);
}

void
nar_add_input_narsese(char *narsese_sentence)
{
	Term term;
	Truth tv;
	char punctuation;
	int tense;
	bool isUserKnowledge;
	double occurrenceTimeOffset;
	narsese_get_sentence(narsese_sentence, &term, &punctuation, &tense, &isUserKnowledge, &tv, &occurrenceTimeOffset);
	//apply reduction rules to term:
	term = rule_table_reduce(term, false);
	if (punctuation == '?')
	{
		//answer questions:
		Truth best_truth = {.frequency = 0.0, .confidence = 1.0};
		Truth best_truth_projected = {0};
		Term best_term = {0};
		long answerOccurrenceTime = OCCURRENCE_ETERNAL;
		long answerCreationTime = 0;
		bool isImplication = narsese_copula_equals(term.atoms[0], '$');
		fputs("Input: ", stdout);
		io_narsese_print_term(&term);
		fputs("?", stdout);
		puts(tense == 1 ? " :|:" : (tense == 2 ? " :\\:" : (tense == 3 ? " :/:" : "")));
		fflush(stdout);
		for (int i = 0; i < g_concepts.itemsAmount; i++)
		{
			Concept *c = g_concepts.items[i].address;
			//compare the predicate of implication, or if it's not an implication, the term
			Term toCompare = isImplication ? term_extract_subterm(&term, 2) : term;
			if (!variable_unify2(&toCompare, &c->term, true).success)
			{
				goto Continue;
			}
			if (isImplication)
			{
				for (int op_k = 0; op_k < OPERATIONS_MAX; op_k++)
				{
					for (int j = 0; j < c->precondition_beliefs[op_k].itemsAmount; j++)
					{
						Implication *imp = &c->precondition_beliefs[op_k].array[j];
						if (!variable_unify2(&term, &imp->term, true).success)
						{
							continue;
						}
						if (truth_expectation(imp->truth) >= truth_expectation(best_truth))
						{
							best_truth = imp->truth;
							best_term = imp->term;
							answerCreationTime = imp->creationTime;
						}
					}
				}
			}
			else if (tense)
			{
				if (c->belief_spike.type != EVENT_TYPE_DELETED && (tense == 1 || tense == 2))
				{
					Truth potential_best_truth = truth_projection(c->belief_spike.truth, c->belief_spike.occurrenceTime,
					                                              g_currentTime);
					if (truth_expectation(potential_best_truth) >= truth_expectation(best_truth_projected))
					{
						best_truth_projected = potential_best_truth;
						best_truth = c->belief_spike.truth;
						best_term = c->belief_spike.term;
						answerOccurrenceTime = c->belief_spike.occurrenceTime;
						answerCreationTime = c->belief_spike.creationTime;
					}
				}
				if (c->predicted_belief.type != EVENT_TYPE_DELETED && (tense == 1 || tense == 3))
				{
					Truth potential_best_truth = truth_projection(c->predicted_belief.truth,
					                                              c->predicted_belief.occurrenceTime, g_currentTime);
					if (truth_expectation(potential_best_truth) >= truth_expectation(best_truth_projected))
					{
						best_truth_projected = potential_best_truth;
						best_truth = c->predicted_belief.truth;
						best_term = c->predicted_belief.term;
						answerOccurrenceTime = c->predicted_belief.occurrenceTime;
						answerCreationTime = c->predicted_belief.creationTime;
					}
				}
			}
			else
			{
				if (c->belief.type != EVENT_TYPE_DELETED &&
					truth_expectation(c->belief.truth) >= truth_expectation(best_truth))
				{
					best_truth = c->belief.truth;
					best_term = c->belief.term;
					answerCreationTime = c->belief.creationTime;
				}
			}
			Continue:;
		}

		fputs("Answer: ", stdout);
		buffer_t *buf_output = buffer_new();
		buffer_append(buf_output, "Answer: ");
		if (best_truth.confidence == 1.0)
		{
			puts("None.");
			buffer_append(buf_output, "None.");
		}
		else
		{
			io_narsese_print_term(&best_term);
			io_narsese_print_term_with_buffer(&best_term, buf_output);
			if (answerOccurrenceTime == OCCURRENCE_ETERNAL)
			{
				printf(". creationTime=%ld ", answerCreationTime);
				buffer_append(buf_output,
				              io_answer_time_as_string(". creationTime=%ld ", answerCreationTime));
			}
			else
			{
				printf(". :|: occurrenceTime=%ld creationTime=%ld ", answerOccurrenceTime, answerCreationTime);
				buffer_append(buf_output,
				              io_answer_time_alt_as_string(
					              ". :|: occurrenceTime=%ld creationTime=%ld ",
					              answerOccurrenceTime,
					              answerCreationTime));
			}
			io_truth_print(&best_truth);
			buffer_append(buf_output, io_truth_as_string(&best_truth));
		}
		app_handle_javascript_output(buffer_string(buf_output));
		buffer_free(buf_output);
		fflush(stdout);
	}
	else
	{ //input beliefs and goals
		// dont add the input if it is an eternal goal
		if (punctuation == '!' && !tense)
		{
			ASSERT(false, "Eternal goals are not supported!\n");
		}
		else
		{
			ASSERT(punctuation != '.' || tense < 2, "Future and past belief events are not supported!\n");
			nar_add_input(term, punctuation == '!' ? EVENT_TYPE_GOAL : EVENT_TYPE_BELIEF, tv, !tense,
			              occurrenceTimeOffset, isUserKnowledge);
		}
	}
}

