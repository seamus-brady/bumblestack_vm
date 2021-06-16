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

#include <stdbool.h>
#include <stdlib.h>
#include "nars_nar.h"
#include "lib_slog.h"

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

#endif
