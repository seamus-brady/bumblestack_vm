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

int
io_process_input(char *input)
{
	char *line = trim(input);
	int input_size = strlen(line);

	// handle empty input
	if (input_size == 0)
	{
		return io_handle_empty_input();
	}

	// handle comments
	if (wildcardcmp(IO_COMMENT, line))
	{
		return io_handle_comments(line);
	}

	// handle rest VM command
	if (wildcardcmp(IO_VM_RESET, line))
	{
		return INPUT_RESET;
	}

	// handle verbose printing on
	if (wildcardcmp(IO_VERBOSE_MODE_ON, line))
	{
		PRINT_DERIVATIONS = true;
		return INPUT_CONTINUE;
	}

	// handle verbose printing off
	if (wildcardcmp(IO_VERBOSE_MODE_OFF, line))
	{
		PRINT_DERIVATIONS = false;
		return INPUT_CONTINUE;
	}

	// handle stats printing
	if (wildcardcmp(IO_PRINT_STATS, line))
	{
		io_stats_print(g_currentTime);
		return INPUT_CONTINUE;
	}

	// handle diagnostics
	if (wildcardcmp(IO_RUN_DIAGNOSTICS, line))
	{
		io_run_diagnostics();
		return INPUT_CONTINUE;
	}

	// handle dumping memory to json
	if (wildcardcmp(IO_DUMP_MEMORY_JSON, line))
	{
		return io_handle_memory_dump();
	}

	// handle quit
	if (wildcardcmp(IO_QUIT, line))
	{
		return INPUT_EXIT;
	}

	// handle babbling operations
	if (wildcardcmp(IO_BABBLE_OPS, line))
	{
		return io_handle_babble_ops(line);
	}

	// handle motor babbling
	if (wildcardcmp(IO_MOTORBABBLE_OFF, line))
	{
		MOTOR_BABBLING_CHANCE = 0.0;
		return INPUT_CONTINUE;
	}

	if (wildcardcmp(IO_MOTORBABBLE_ON, line))
	{
		MOTOR_BABBLING_CHANCE = MOTOR_BABBLING_CHANCE_INITIAL;
		return INPUT_CONTINUE;
	}

	if (wildcardcmp(IO_MOTORBABBLE_SET, line))
	{
		return io_handle_set_motorbabbble(line);
	}

	// handle add operation
	if (wildcardcmp(IO_ADD_OPERATION, line))
	{
		return io_handle_add_operation(line);
	}

	// handle cycle request
	if (wildcardcmp(IO_CYCLE, line))
	{
		return io_handle_run_cycle(line);
	}

	if(!nar_validate_input_narsese(line)){
		fflush(stdout);
		return INPUT_CONTINUE_WITH_ERROR;
	} else {
		// last but not least, add input narsese
		nar_add_input_narsese(line);
		fflush(stdout);
		return INPUT_CONTINUE;
	}
}

void
io_generic_operation_handler(Term term)
{
	// a placeholder
	slog_info("Generic operation handler invoked.");
}

int
io_handle_run_cycle(const char *line)
{
	unsigned int steps;
	sscanf(line, "%u", &steps);
	slog_info("Performing %u inference steps...", steps);
	fflush(stdout);
	nar_cycles(steps);
	slog_info("Completed %u additional inference steps.", steps);
	fflush(stdout);
	return INPUT_CONTINUE;
}

int
io_handle_add_operation(const char *line)
{
	// this just adds the new type of script operations
	char incoming_term_string[NARSESE_LEN_MAX];
	char incoming_script[NARSESE_LEN_MAX];
	sscanf(
		&line[strlen(IO_ADD_OPERATION_SET)],
		"%s %s",
		incoming_term_string,
		incoming_script);
	// make sure there is a '^' char at the start
	char *term_string = NULL;
	slog_info("Term string supplied is %s", incoming_term_string);
	slog_info("Action constant string supplied is %s", incoming_script);
	if (!wildcardcmp(IO_OP_PREFIX, (const char *) incoming_term_string))
	{
		buffer_t *buf = buffer_new();
		buffer_prepend(buf, IO_OP_CHAR);
		term_string = buffer_string(buf);
		buffer_free(buf);
	}
	else
	{
		term_string = (char *) incoming_term_string;
	}
	// TODO add proper validation somewhere :)
	ASSERT(strlen(term_string) > 0, "Term string supplied is too short.");
	ASSERT(strlen(incoming_script) > 0, "Script constant supplied is too short.");
	nar_add_operation(
		narsese_atomic_term(term_string),
		(Action) io_generic_operation_handler, // use a generic action handler
		(char *) incoming_script);
	slog_info("Operation added.");
	return INPUT_CONTINUE;
}

int
io_handle_set_motorbabbble(const char *line)
{
	sscanf(&line[strlen("*VM_MOTORBABBLE=")], "%lf", &MOTOR_BABBLING_CHANCE);
	return INPUT_CONTINUE;
}

int
io_handle_memory_dump()
{
	io_print_atom_table();
	io_print_concepts();
	io_print_cycling_belief_events();
	io_print_cycling_goal_events();
	return INPUT_CONTINUE;
}

int
io_handle_babble_ops(const char *line)
{
	sscanf(&line[strlen("IO_BABBLE_OPS=")], "%d", &BABBLING_OPS);
	return INPUT_CONTINUE;
}

int
io_handle_comments(const char *line)
{
	slog_info("Comment from input: ", stdout);
	puts(&line[2]);
	fflush(stdout);
	return INPUT_CONTINUE;
}

int
io_handle_empty_input()
{
	nar_cycles(1);
	fflush(stdout);
	return INPUT_CONTINUE;
}

void
io_diagnostic_test_operation(Term term)
{
	slog_info("Diagnostic test operation was run correctly.");
	diagnosticTestOperationRun = true;
}

void
io_run_operation_diagnostic()
{
	slog_info("Running operation diagnostic test...");
	slog_info("Add operation...");
	nar_add_operation(narsese_atomic_term("^op"), io_diagnostic_test_operation, "TEST_ACTION");
	slog_info("Add belief...");
	nar_add_input_Belief(narsese_atomic_term("a"));
	slog_info("Run 1 inference cycle...");
	nar_cycles(1);
	slog_info("Add belief...");
	nar_add_input_Belief(narsese_atomic_term("^op"));
	slog_info("Run 1 inference cycle...");
	nar_cycles(1);
	slog_info("Add belief...");
	nar_add_input_Belief(narsese_atomic_term("result"));
	slog_info("Run 1 inference cycle...");
	nar_cycles(1);
	slog_info("Add belief...");
	nar_add_input_Belief(narsese_atomic_term("a"));
	slog_info("Run 1 inference cycle...");
	nar_cycles(1);
	slog_info("Add goal...");
	nar_add_input_goal(narsese_atomic_term("result"));
	slog_info("Run 1 inference cycle...");
	nar_cycles(1);
	slog_info("Finished operation diagnostic test.");
}

void
io_run_ruletable_diagnostic()
{
	slog_info("Running a diagnostic ruletable test...");
	slog_info("Adding input...");
	nar_add_input(narsese_term(
		"<cat --> animal>"), EVENT_TYPE_BELIEF, NAR_DEFAULT_TRUTH,
	              true, 0, false);
	slog_info("Adding input...");
	nar_add_input(narsese_term(
		"<animal --> being>"), EVENT_TYPE_BELIEF, NAR_DEFAULT_TRUTH,
	              true, 0, false);
	slog_info("Running 10 inference cycles...");
	nar_cycles(10);
	ASSERT(g_currentTime != 0, "Internal cycle time should not be zero.");
	slog_info("Finished diagnostic ruletable test.");
}

void
io_run_diagnostics(void)
{
	slog_info("Running diagnostic tests...");
	io_run_ruletable_diagnostic();
	io_run_operation_diagnostic();
	slog_info("Completed diagnostic tests...");
}

void
io_setup_logging()
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
	// disable color output - looks weird in browser
	slgCfg.eColorFormat = SLOG_COLOR_DISABLE;
	slog_config_set(&slgCfg);
}

void
io_print_concepts()
{
	slog_info("Printing concepts:");
	for (int opi = 0; opi < OPERATIONS_MAX; opi++)
	{
		if (g_operations[opi].term.atoms[0])
		{
			printf("Operation %d ", opi + 1);
			io_narsese_print_term(&g_operations[opi].term);
			puts("");
		}
	}
	for (int i = 0; i < g_concepts.itemsAmount; i++)
	{
		Concept *c = g_concepts.items[i].address;
		ASSERT(c != NULL, "Concept is null");
		fputs("//", stdout);
		io_narsese_print_term(&c->term);
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
		io_narsese_print_term(&left);
		fputs("\", ", stdout);
		fputs("\"", stdout);
		io_narsese_print_term(&right);
		fputs("\", ", stdout);
		fputs("\"", stdout);
		io_narsese_print_term(&left_left);
		fputs("\", ", stdout);
		fputs("\"", stdout);
		io_narsese_print_term(&left_right);
		fputs("\", ", stdout);
		fputs("\"", stdout);
		io_narsese_print_term(&right_left);
		fputs("\", ", stdout);
		fputs("\"", stdout);
		io_narsese_print_term(&right_right);
		fputs("\"", stdout);
		puts("]}");
		if (c->belief.type != EVENT_TYPE_DELETED)
		{
			io_memory_print_added_event(&c->belief, 1, true, false, false, false);
		}
		for (int opi = 0; opi < OPERATIONS_MAX; opi++)
		{
			for (int h = 0; h < c->precondition_beliefs[opi].itemsAmount; h++)
			{
				Implication *imp = &c->precondition_beliefs[opi].array[h];
				io_memory_print_added_implication(&imp->term, &imp->truth, imp->occurrenceTimeOffset, 1, true, false,
				                                  false);
			}
		}
	}
	slog_info("Finished printing concepts.");
}

void
io_print_atom_table()
{
	inverted_atom_index_print();
}

void
io_print_cycling_belief_events()
{
	slog_info("Printing cycling belief events:");
	for (int i = 0; i < g_cyclingBeliefEvents.itemsAmount; i++)
	{
		Event *e = g_cyclingBeliefEvents.items[i].address;
		ASSERT(e != NULL, "Event is null");
		io_narsese_print_term(&e->term);
		printf(": { \"priority\": %f, \"time\": %ld } ", g_cyclingBeliefEvents.items[i].priority,
		       e->occurrenceTime);
		io_truth_print(&e->truth);
	}
	slog_info("Finished printing cycling belief events.");
}

void
io_print_cycling_goal_events()
{
	slog_info("Printing cycling goal events:");
	for (int i = 0; i < g_cyclingGoalEvents.itemsAmount; i++)
	{
		Event *e = g_cyclingGoalEvents.items[i].address;
		ASSERT(e != NULL, "Event is null");
		io_narsese_print_term(&e->term);
		printf(": {\"priority\": %f, \"time\": %ld } ", g_cyclingGoalEvents.items[i].priority,
		       e->occurrenceTime);
		io_truth_print(&e->truth);
	}
	slog_info("Finished printing cycling goal events.");
}

void
io_print_decision(Decision decision, Implication bestImp)
{
	printf("Decision expectation=(%f) implication: ", decision.desire);
	io_narsese_print_term(&bestImp.term);
	printf(". truth=(frequency=%f confidence=%f) occurrenceTimeOffset=(%f)",
	       bestImp.truth.frequency,
	       bestImp.truth.confidence,
	       bestImp.occurrenceTimeOffset);
	fputs(" precondition: ", stdout);
	io_narsese_print_term(&decision.reason->term);
	fputs(". :|: ", stdout);
	printf("truth=(frequency=%f confidence=%f)", decision.reason->truth.frequency, decision.reason->truth.confidence);
	printf(" occurrenceTime=(%ld)\n", decision.reason->occurrenceTime);
}

void
io_print_decision_with_json(Decision decision, Implication bestImp)
{
	printf("{\"output\": {");
	// TODO - should be on one line
	printf("\"decision\": {");
	printf("\"expectation\": \"%f\", ", decision.desire);
	printf("\"implication\": { \"narsese_term\": \"");
	io_narsese_print_term(&bestImp.term);
	printf(".\", ");
	printf("\"truth\": { \"frequency\": \"%f\", \"confidence\": \"%f\"}, \"occurrence_time_offset\": \"%f\" },",
	       bestImp.truth.frequency,
	       bestImp.truth.confidence,
	       bestImp.occurrenceTimeOffset);
	fputs(" \"precondition \": { \"narsese_term\": \"", stdout);
	io_narsese_print_term(&decision.reason->term);
	fputs(". :|: \", ", stdout);
	printf("\"truth\": { \"frequency\": \"%f\", \"confidence\": \"%f\"}, \"occurrence_time\": \"%ld\" }",
	       decision.reason->truth.frequency, decision.reason->truth.confidence, decision.reason->occurrenceTime);
	puts("}}}");
}

void
io_narsese_print_term_with_buffer(Term *term, buffer_t *buf)
{
	io_narsese_print_term_pretty_recursive_with_buffer(term, 1, buf);
}

void
io_narsese_print_term_pretty_recursive_with_buffer(Term *term, int index, buffer_t *buf) //start with index=1!
{
	Atom atom = term->atoms[index - 1];
	if (!atom)
	{
		return;
	}
	int child1 = index * 2;
	int child2 = index * 2 + 1;
	bool hasLeftChild = child1 < COMPOUND_TERM_SIZE_MAX && term->atoms[child1 - 1];
	bool hasRightChild = child2 < COMPOUND_TERM_SIZE_MAX && term->atoms[child2 - 1] &&
		!narsese_copula_equals(term->atoms[child2 - 1], '@');
	bool isNegation = narsese_copula_equals(atom, '!');
	bool isExtSet = narsese_copula_equals(atom, '"');
	bool isIntSet = narsese_copula_equals(atom, '\'');
	bool isStatement =
		narsese_copula_equals(atom, '$') || narsese_copula_equals(atom, ':') || narsese_copula_equals(atom, '=');
	if (isExtSet)
	{
		buffer_append(buf, hasLeftChild ? "{" : "");
	}
	else if (isIntSet)
	{
		buffer_append(buf, hasLeftChild ? "[" : "");
	}
	else if (isStatement)
	{
		buffer_append(buf, hasLeftChild ? "<" : "");
	}
	else
	{
		buffer_append(buf, hasLeftChild ? "(" : "");
		if (isNegation)
		{
			io_narsese_print_atom_with_buffer(atom, buf);
			buffer_append(buf, " ");
		}
	}
	if (child1 < COMPOUND_TERM_SIZE_MAX)
	{
		io_narsese_print_term_pretty_recursive_with_buffer(term, child1, buf);
	}
	if (hasRightChild)
	{
		buffer_append(buf, hasLeftChild ? " " : "");
	}
	if (!isExtSet && !isIntSet && !narsese_copula_equals(atom, '@'))
	{
		if (!isNegation)
		{
			io_narsese_print_atom_with_buffer(atom, buf);
			buffer_append(buf, hasLeftChild ? " " : "");
		}
	}
	if (child2 < COMPOUND_TERM_SIZE_MAX)
	{
		io_narsese_print_term_pretty_recursive_with_buffer(term, child2, buf);
	}
	if (isExtSet)
	{
		buffer_append(buf, hasLeftChild ? "}" : "");
	}
	else if (isIntSet)
	{
		buffer_append(buf, hasLeftChild ? "]" : "");
	}
	else if (isStatement)
	{
		buffer_append(buf, hasLeftChild ? ">" : "");
	}
	else
	{
		buffer_append(buf, hasLeftChild ? ")" : "");
	}
}

void
io_narsese_print_atom_with_buffer(Atom atom, buffer_t *buf)
{
	if (atom)
	{
		if (narsese_copula_equals(atom, ':'))
		{
			buffer_append(buf, "-->");
		}
		else if (narsese_copula_equals(atom, '$'))
		{
			buffer_append(buf, "=/>");
		}
		else if (narsese_copula_equals(atom, '+'))
		{
			buffer_append(buf, "&/");
		}
		else if (narsese_copula_equals(atom, ';'))
		{
			buffer_append(buf, "&|");
		}
		else if (narsese_copula_equals(atom, '='))
		{
			buffer_append(buf, "<->");
		}
		else if (narsese_copula_equals(atom, '/'))
		{
			buffer_append(buf, "/1");
		}
		else if (narsese_copula_equals(atom, '%'))
		{
			buffer_append(buf, "/2");
		}
		else if (narsese_copula_equals(atom, '\\'))
		{
			buffer_append(buf, "\\1");
		}
		else if (narsese_copula_equals(atom, '#'))
		{
			buffer_append(buf, "\\2");
		}
		else
		{
			buffer_append(buf, g_narsese_atomNames[atom - 1]);
		}
	}
	else
	{
		buffer_append(buf, "@");
	}
}

void
io_narsese_print_term(Term *term)
{
	io_narsese_print_term_pretty_recursive(term, 1);
}

void
io_narsese_print_term_pretty_recursive(Term *term, int index) //start with index=1!
{
	Atom atom = term->atoms[index - 1];
	if (!atom)
	{
		return;
	}
	int child1 = index * 2;
	int child2 = index * 2 + 1;
	bool hasLeftChild = child1 < COMPOUND_TERM_SIZE_MAX && term->atoms[child1 - 1];
	bool hasRightChild = child2 < COMPOUND_TERM_SIZE_MAX && term->atoms[child2 - 1] &&
		!narsese_copula_equals(term->atoms[child2 - 1], '@');
	bool isNegation = narsese_copula_equals(atom, '!');
	bool isExtSet = narsese_copula_equals(atom, '"');
	bool isIntSet = narsese_copula_equals(atom, '\'');
	bool isStatement =
		narsese_copula_equals(atom, '$') || narsese_copula_equals(atom, ':') || narsese_copula_equals(atom, '=');
	if (isExtSet)
	{
		fputs(hasLeftChild ? "{" : "", stdout);
	}
	else if (isIntSet)
	{
		fputs(hasLeftChild ? "[" : "", stdout);
	}
	else if (isStatement)
	{
		fputs(hasLeftChild ? "<" : "", stdout);
	}
	else
	{
		fputs(hasLeftChild ? "(" : "", stdout);
		if (isNegation)
		{
			io_narsese_print_atom(atom);
			fputs(" ", stdout);
		}
	}
	if (child1 < COMPOUND_TERM_SIZE_MAX)
	{
		io_narsese_print_term_pretty_recursive(term, child1);
	}
	if (hasRightChild)
	{
		fputs(hasLeftChild ? " " : "", stdout);
	}
	if (!isExtSet && !isIntSet && !narsese_copula_equals(atom, '@'))
	{
		if (!isNegation)
		{
			io_narsese_print_atom(atom);
			fputs(hasLeftChild ? " " : "", stdout);
		}
	}
	if (child2 < COMPOUND_TERM_SIZE_MAX)
	{
		io_narsese_print_term_pretty_recursive(term, child2);
	}
	if (isExtSet)
	{
		fputs(hasLeftChild ? "}" : "", stdout);
	}
	else if (isIntSet)
	{
		fputs(hasLeftChild ? "]" : "", stdout);
	}
	else if (isStatement)
	{
		fputs(hasLeftChild ? ">" : "", stdout);
	}
	else
	{
		fputs(hasLeftChild ? ")" : "", stdout);
	}
}

void
io_narsese_print_atom(Atom atom)
{
	if (atom)
	{
		if (narsese_copula_equals(atom, ':'))
		{
			fputs("-->", stdout);
		}
		else if (narsese_copula_equals(atom, '$'))
		{
			fputs("=/>", stdout);
		}
		else if (narsese_copula_equals(atom, '+'))
		{
			fputs("&/", stdout);
		}
		else if (narsese_copula_equals(atom, ';'))
		{
			fputs("&|", stdout);
		}
		else if (narsese_copula_equals(atom, '='))
		{
			fputs("<->", stdout);
		}
		else if (narsese_copula_equals(atom, '/'))
		{
			fputs("/1", stdout);
		}
		else if (narsese_copula_equals(atom, '%'))
		{
			fputs("/2", stdout);
		}
		else if (narsese_copula_equals(atom, '\\'))
		{
			fputs("\\1", stdout);
		}
		else if (narsese_copula_equals(atom, '#'))
		{
			fputs("\\2", stdout);
		}
		else
		{
			fputs(g_narsese_atomNames[atom - 1], stdout);
		}
	}
	else
	{
		fputs("@", stdout);
	}
}

static void
io_memory_print_added_knowledge(Term *term, char type, Truth *truth, long occurrenceTime, double occurrenceTimeOffset,
                                double priority, bool input, bool derived, bool revised, bool controlInfo)
{
	if (((input && PRINT_INPUT) || PRINT_DERIVATIONS) && priority > PRINT_DERIVATIONS_PRIORITY_THRESHOLD &&
		(input || derived || revised))
	{
		if (controlInfo)
			fputs(revised ? "Revised: " : (input ? "Input: " : "Derived: "), stdout);
		if (narsese_copula_equals(term->atoms[0], '$'))
			printf("occurrenceTimeOffset=(%f) ", occurrenceTimeOffset);
		io_narsese_print_term(term);
		fputs((type == EVENT_TYPE_BELIEF ? ". " : "! "), stdout);
		if (occurrenceTime != OCCURRENCE_ETERNAL)
		{
			printf(":|: occurrenceTime=(%ld) ", occurrenceTime);
		}
		if (controlInfo)
		{
			printf("priority=(%f) ", priority);
			io_truth_print(truth);
		}
		else
		{
			io_truth_print2(truth);
		}
		fflush(stdout);
	}
}

void
io_memory_print_added_event(Event *event, double priority, bool input, bool derived, bool revised, bool controlInfo)
{
	io_memory_print_added_knowledge(&event->term, event->type, &event->truth, event->occurrenceTime, 0, priority, input,
	                                derived, revised, controlInfo);
}

void
io_memory_print_added_implication(Term *implication,
                                  Truth *truth,
                                  double occurrenceTimeOffset,
                                  double priority,
                                  bool input,
                                  bool revised,
                                  bool controlInfo)
{
	io_memory_print_added_knowledge(implication, EVENT_TYPE_BELIEF, truth, OCCURRENCE_ETERNAL, occurrenceTimeOffset,
	                                priority, input, true, revised, controlInfo);
}

void
io_stamp_print(Stamp *stamp)
{
	fputs("stamp=", stdout);
	for (int i = 0; i < STAMP_SIZE; i++)
	{
		if (stamp->evidentialBase[i] == STAMP_FREE)
		{
			break;
		}
		printf("%ld,", stamp->evidentialBase[i]);
	}
	puts("");
}

void
io_stats_print(long currentTime)
{
	stats_print(currentTime);
}

void
io_truth_print(Truth *truth)
{
	printf(" truth=(frequency=%f, confidence=%f) \n", truth->frequency, truth->confidence);
}

void
io_truth_print2(Truth *truth)
{
	printf("{%f %f} \n", truth->frequency, truth->confidence);
}

void
io_usage_print(Usage *usage)
{
	printf("Usage: useCount=%ld lastUsed=%ld\n", usage->useCount, usage->lastUsed);
}
