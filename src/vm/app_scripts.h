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

#define JAVASCRIPT_ACTION_HANDLER "bumblevm_action_handler"

#include "lib_slog.h"
#include "lib_buffer.h"
#include "nars_term.h"
#include <emscripten.h>

void
app_handle_operation_action(char *operation_script, char *String);

void
app_handle_javascript_operation_action(char *term_string, char *script);

#endif //BUMBLESTACK_SRC_VM_APP_SCRIPTS_H
