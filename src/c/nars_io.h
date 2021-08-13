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

#ifndef H_IO
#define H_IO

#include "lib_slog.h"
#include "lib_trim.h"
#include "lib_wildcardcmp.h"
#include "nars_decision.h"
#include "nars_nar.h"
#include <stdbool.h>
#include <stdlib.h>

#define INPUT_CONTINUE 0
#define INPUT_CONTINUE_WITH_ERROR 1
#define INPUT_RESET 3
#define INPUT_EXIT 4

static char *const REPL_PROMPT = "BUMBLESTACK $> ";
static const int REPL_EXIT = 99;
static char *const IO_COMMENT = "//*";
static char *const IO_VM_RESET = "system-reset*";
static char *const IO_VERBOSE_MODE_ON = "verbose-mode on*";
static char *const IO_VERBOSE_MODE_OFF = "verbose-mode off*";
static char *const IO_PRINT_STATS = "print-stats*";
static char *const IO_RUN_DIAGNOSTICS = "run-diagnostics*";
static char *const IO_DUMP_MEMORY_JSON = "dump-memory*";
static char *const IO_QUIT = "quit*";
static char *const IO_BABBLE_OPS = "babble-ops*";
static char *const IO_MOTORBABBLE_OFF = "motorbabble off*";
static char *const IO_MOTORBABBLE_ON = "motorbabble on*";
static char *const IO_MOTORBABBLE_SET = "motorbabble=*";
static char *const IO_ADD_OPERATION = "add-operation*";
static char *const IO_ADD_OPERATION_SET = "add-operation ";
static char *const IO_OP_PREFIX = "^*";
static char *const IO_OP_CHAR = "^";
static char *const IO_CYCLE = "cycle*";
static char *const IO_CYCLE_SET = "cycle ";

void
io_generic_operation_handler();

int
io_handle_run_cycle(const char *line);

int
io_handle_add_operation(char *term_string, Action action);

int
io_handle_run_cycle(const char *line);

int
io_handle_empty_input();

int
io_handle_set_motorbabbble(const char *line);

int
io_handle_memory_dump();

int
io_handle_babble_ops(const char *line);

int
io_handle_comments(const char *line);

void
io_setup_logging();

void
io_print_concepts();

void
io_print_atom_table();

void
io_print_cycling_belief_events();

void
io_print_cycling_goal_events();

void
io_run_diagnostics();

// main shell process
int
io_process_input(char *line);

void
io_print_decision_with_json(Decision decision, Implication imp);

//Print an atom with buffer
void
io_narsese_print_atom_with_buffer(Atom atom, buffer_t *buf);

//Print a term with a buffer
void
io_narsese_print_term_with_buffer(Term *term, buffer_t *buf);

void
io_narsese_print_term_pretty_recursive_with_buffer(Term *term, int index, buffer_t *buf);

void
io_narsese_print_term_pretty_recursive(Term *term, int index);

//Print an atom
void
io_narsese_print_atom(Atom atom);

//Print a term
void
io_narsese_print_term(Term *term);

//Print an event in memory:
void
io_memory_print_added_event(Event *event, double priority, bool input, bool derived, bool revised, bool controlInfo);

//Print an implication in memory:
void
io_memory_print_added_implication(Term *implication,
                                  Truth *truth,
                                  double occurrenceTimeOffset,
                                  double priority,
                                  bool input,
                                  bool revised,
                                  bool controlInfo);

//print stamp
void
io_stamp_print(Stamp *stamp);

void
io_stats_print(long currentTime);

void
io_truth_print(Truth *truth);

void
io_truth_print2(Truth *truth);

char *
io_truth_as_string(Truth *truth);

void
io_print_decision(Decision decision, Implication bestImp);

//print usage
void
io_usage_print(Usage *usage);

char *
io_answer_time_as_string(char *fmt, long answerCreationTime);

char *
io_answer_time_alt_as_string(char *fmt, long answerOccurrenceTime, long answerCreationTime);

#endif
