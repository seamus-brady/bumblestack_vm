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

#include "nars_io.h"

bool diagnosticTestOperationRun = false;

void
diagnosticTestOperation(Term term)
{
	slog_info("Diagnostic test operation was run correctly.");
	diagnosticTestOperationRun = true;
}

void
run_operation_diagnostic()
{
	slog_info("Running operation diagnostic test...");
	slog_info("Add operation...");
	NAR_AddOperation(narsese_atomic_term("^op"), diagnosticTestOperation);
	slog_info("Add belief...");
	NAR_AddInputBelief(narsese_atomic_term("a"));
	slog_info("Run 1 inference cycle...");
	NAR_Cycles(1);
	slog_info("Add belief...");
	NAR_AddInputBelief(narsese_atomic_term("^op"));
	slog_info("Run 1 inference cycle...");
	NAR_Cycles(1);
	slog_info("Add belief...");
	NAR_AddInputBelief(narsese_atomic_term("result"));
	slog_info("Run 1 inference cycle...");
	NAR_Cycles(1);
	slog_info("Add belief...");
	NAR_AddInputBelief(narsese_atomic_term("a"));
	slog_info("Run 1 inference cycle...");
	NAR_Cycles(1);
	slog_info("Add goal...");
	NAR_AddInputGoal(narsese_atomic_term("result"));
	slog_info("Run 1 inference cycle...");
	NAR_Cycles(1);
	slog_info("Finished operation diagnostic test.");
}

void
run_ruletable_diagnostic()
{
	slog_info("Running a diagnostic ruletable test...");
	slog_info("Adding input...");
	NAR_AddInput(narsese_term(
		"<cat --> animal>"), EVENT_TYPE_BELIEF, NAR_DEFAULT_TRUTH,
	             true, 0, false);
	slog_info("Adding input...");
	NAR_AddInput(narsese_term(
		"<animal --> being>"), EVENT_TYPE_BELIEF, NAR_DEFAULT_TRUTH,
	             true, 0, false);
	slog_info("Running 10 inference cycles...");
	NAR_Cycles(10);
	ASSERT(g_currentTime != 0, "Internal cycle time should not be zero.");
	slog_info("Finished diagnostic ruletable test.");
}

void
run_diagnostics(void)
{
	slog_info("Running diagnostic tests...");
	run_ruletable_diagnostic();
	run_operation_diagnostic();
	slog_info("Completed diagnostic tests...");
}

void
setup_logging()
{// Enable all logging levels
	int enabledLevels = SLOG_FLAGS_ALL;

	// check debug logs
	if (!DEBUG_MODE)
	{
		slog_disable(SLOG_DEBUG);
	}

	// init log system with no file output
	slog_init(NULL, enabledLevels, 0);

	// logging config
	SLogConfig slgCfg;
	slog_config_get(&slgCfg);

	// Enable date + time in output
	slgCfg.eDateControl = SLOG_DATE_FULL;
	slog_config_set(&slgCfg);
}

void
print_concepts()
{
	slog_info("Printing g_concepts:");
	for (int opi = 0; opi < OPERATIONS_MAX; opi++)
	{
		if (g_operations[opi].term.atoms[0])
		{
			printf("*setopname %d ", opi + 1);
			narsese_print_term(&g_operations[opi].term);
			puts("");
		}
	}
	for (int i = 0; i < g_concepts.itemsAmount; i++)
	{
		Concept *c = g_concepts.items[i].address;
		ASSERT(c != NULL, "Concept is null");
		fputs("//", stdout);
		narsese_print_term(&c->term);
		printf(
			": { \"priority\": %f, \"usefulness\": %f, \"useCount\": %ld, \"lastUsed\": %ld, \"frequency\": %f, \"confidence\": %f, \"termlinks\": [",
			c->priority,
			g_concepts.items[i].priority,
			c->usage.useCount,
			c->usage.lastUsed,
			c->belief.truth.frequency,
			c->belief.truth.confidence);
		Term left = term_extract_subterm(&c->term, 1);
		Term left_left = term_extract_subterm(&left, 1);
		Term left_right = term_extract_subterm(&left, 2);
		Term right = term_extract_subterm(&c->term, 2);
		Term right_left = term_extract_subterm(&right, 1);
		Term right_right = term_extract_subterm(&right, 2);
		fputs("\"", stdout);
		narsese_print_term(&left);
		fputs("\", ", stdout);
		fputs("\"", stdout);
		narsese_print_term(&right);
		fputs("\", ", stdout);
		fputs("\"", stdout);
		narsese_print_term(&left_left);
		fputs("\", ", stdout);
		fputs("\"", stdout);
		narsese_print_term(&left_right);
		fputs("\", ", stdout);
		fputs("\"", stdout);
		narsese_print_term(&right_left);
		fputs("\", ", stdout);
		fputs("\"", stdout);
		narsese_print_term(&right_right);
		fputs("\"", stdout);
		puts("]}");
		if (c->belief.type != EVENT_TYPE_DELETED)
		{
			memory_print_added_event(&c->belief, 1, true, false, false, false);
		}
		for (int opi = 0; opi < OPERATIONS_MAX; opi++)
		{
			for (int h = 0; h < c->precondition_beliefs[opi].itemsAmount; h++)
			{
				Implication *imp = &c->precondition_beliefs[opi].array[h];
				Memory_printAddedImplication(&imp->term, &imp->truth, imp->occurrenceTimeOffset, 1, true, false,
				                             false);
			}
		}
	}
	slog_info("Finished printing g_concepts.");
}

void
print_atom_table()
{
	inverted_atom_index_print();
}

void
print_cycling_belief_events()
{
	slog_info("Printing cycling g_beliefEvents:");
	for (int i = 0; i < g_cyclingBeliefEvents.itemsAmount; i++)
	{
		Event *e = g_cyclingBeliefEvents.items[i].address;
		ASSERT(e != NULL, "Event is null");
		narsese_print_term(&e->term);
		printf(": { \"priority\": %f, \"time\": %ld } ", g_cyclingBeliefEvents.items[i].priority,
		       e->occurrenceTime);
		truth_print(&e->truth);
	}
	slog_info("Finished printing cycling g_beliefEvents.");
}

void
print_cycling_goal_events()
{
	slog_info("Printing cycling goal events:");
	for (int i = 0; i < g_cyclingGoalEvents.itemsAmount; i++)
	{
		Event *e = g_cyclingGoalEvents.items[i].address;
		ASSERT(e != NULL, "Event is null");
		narsese_print_term(&e->term);
		printf(": {\"priority\": %f, \"time\": %ld } ", g_cyclingGoalEvents.items[i].priority,
		       e->occurrenceTime);
		truth_print(&e->truth);
	}
	slog_info("Finished printing cycling goal events.");
}