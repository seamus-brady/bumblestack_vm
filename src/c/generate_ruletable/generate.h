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

#include "nars/nars_ruletable.h"
#include <stdlib.h>
// the old 'ruletable.c' file is included to stop build errors
#include "nars/nars_cycle.c"
#include "nars/nars_cycle.h"
#include "nars/nars_decision.c"
#include "nars/nars_decision.h"
#include "nars/nars_event.c"
#include "nars/nars_event.h"
#include "nars/nars_fifo.c"
#include "nars/nars_fifo.h"
#include "nars/nars_globals.c"
#include "nars/nars_globals.h"
#include "nars/nars_hashtable.c"
#include "nars/nars_hashtable.h"
#include "nars/nars_inference.c"
#include "nars/nars_inference.h"
#include "nars/nars_inverted_atom_index.c"
#include "nars/nars_inverted_atom_index.h"
#include "nars/nars_memory.c"
#include "nars/nars_memory.h"
#include "nars/nars_nal.c"
#include "nars/nars_nal.h"
#include "nars/nars_nar.c"
#include "nars/nars_nar.h"
#include "nars/nars_narsese.c"
#include "nars/nars_narsese.h"
#include "nars/nars_priority_queue.c"
#include "nars/nars_priority_queue.h"
#include "nars/nars_ruletable.c"
#include "nars/nars_stack.c"
#include "nars/nars_stack.h"
#include "nars/nars_stamp.c"
#include "nars/nars_stamp.h"
#include "nars/nars_stats.c"
#include "nars/nars_stats.h"
#include "nars/nars_table.c"
#include "nars/nars_table.h"
#include "nars/nars_term.c"
#include "nars/nars_term.h"
#include "nars/nars_truth.c"
#include "nars/nars_truth.h"
#include "nars/nars_usage.c"
#include "nars/nars_usage.h"
#include "nars/nars_variable.c"
#include "nars/nars_variable.h"