/*
 * Copyright 2021 seamus@bumblestack.com, Corvideon Limited.
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

#ifndef BUMBLESTACK_SRC_VM_APP_REPL_H
#define BUMBLESTACK_SRC_VM_APP_REPL_H

#include "repl_repl.h"
#include "nars_io.h"

repl_session_opts g_repl_opts;

void
system_reset();

int
app_repl_main();

static char *
app_repl_eval(repl_session_t *sess, char *buf);

static void
app_repl_print(repl_session_t *sess, char *buf);

static void
app_repl_error(repl_session_t *sess, char *err);

#endif //BUMBLESTACK_SRC_VM_APP_REPL_H
