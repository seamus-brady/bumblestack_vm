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

#include "../app_scripts.c"
#include "../app_scripts.h"
#include "lib_buffer.c"
#include "lib_buffer.h"
#include "lib_fs.c"
#include "lib_fs.h"
#include "lib_slog.c"
#include "lib_slog.h"
#include "lib_strsplit.c"
#include "lib_strsplit.h"
#include "lib_trim.c"
#include "lib_trim.h"
#include "lib_wildcardcmp.c"
#include "lib_wildcardcmp.h"
#include "nars_cycle.c"
#include "nars_cycle.h"
#include "nars_decision.c"
#include "nars_decision.h"
#include "nars_event.c"
#include "nars_event.h"
#include "nars_fifo.c"
#include "nars_fifo.h"
#include "nars_globals.c"
#include "nars_globals.h"
#include "nars_hashtable.c"
#include "nars_hashtable.h"
#include "nars_inference.c"
#include "nars_inference.h"
#include "nars_inverted_atom_index.c"
#include "nars_inverted_atom_index.h"
#include "nars_io.c"
#include "nars_io.h"
#include "nars_memory.c"
#include "nars_memory.h"
#include "nars_nal.c"
#include "nars_nal.h"
#include "nars_nar.c"
#include "nars_nar.h"
#include "nars_narsese.c"
#include "nars_narsese.h"
#include "nars_priority_queue.c"
#include "nars_priority_queue.h"
#include "nars_ruletable.c"
#include "nars_ruletable.h"
#include "nars_stack.c"
#include "nars_stack.h"
#include "nars_stamp.c"
#include "nars_stamp.h"
#include "nars_stats.c"
#include "nars_stats.h"
#include "nars_table.c"
#include "nars_table.h"
#include "nars_term.c"
#include "nars_term.h"
#include "nars_truth.c"
#include "nars_truth.h"
#include "nars_usage.c"
#include "nars_usage.h"
#include "nars_variable.c"
#include "nars_variable.h"
#include "unity/unity.h"
