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

#include "unity/unity.h"
#include "../fifo.h"
#include "../fifo.c"
#include "../globals.h"
#include "../globals.c"
#include "../narsese.h"
#include "../narsese.c"
#include "../hashtable.h"
#include "../hashtable.c"
#include "../variable.h"
#include "../variable.c"
#include "../term.h"
#include "../term.c"
#include "../inference.h"
#include "../inference.c"
#include "../stack.h"
#include "../stack.c"
#include "../stamp.h"
#include "../stamp.c"
#include "../truth.h"
#include "../truth.c"
#include "../invertedAtomIndex.h"
#include "../invertedAtomIndex.c"
#include "../priorityqueue.h"
#include "../priorityqueue.c"
#include "../table.h"
#include "../table.c"
#include "../memory.h"
#include "../memory.c"
#include "../event.h"
#include "../event.c"
#include "../usage.h"
#include "../usage.c"
#include "../nar.h"
#include "../nar.c"
#include "../cycle.h"
#include "../cycle.c"
#include "../decision.h"
#include "../decision.c"
#include "../nal.h"
#include "../nal.c"
#include "../ruletable.h"
#include "../ruletable.c"
#include "../stats.h"
#include "../stats.c"
#include "../slog.h"
#include "../slog.c"
#include "../io.h"
#include "../io.c"
#include "../cJSON.h"
#include "../cJSON.c"
