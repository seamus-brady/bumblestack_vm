/*
 * Copyright 2021 seamus@bumblestack.com, Corvideon Limited.

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
#ifndef BUMBLESTACK_SRC_VM_APP_SCRIPTS_H
#define BUMBLESTACK_SRC_VM_APP_SCRIPTS_H

#include "lib/lib_buffer.h"
#include "lib/lib_fs.h"
#include "lib/lib_slog.h"
#include "lib/lib_strsplit.h"
#include "nars/nars_io.h"
#include "nars/nars_term.h"

void
app_handle_operation_action(Decision *decision);

#endif //BUMBLESTACK_SRC_VM_APP_SCRIPTS_H
