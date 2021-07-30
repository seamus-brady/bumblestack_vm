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
#define JAVASCRIPT_OUTPUT_HANDLER "bumblevm_output_handler"

#include "lib_slog.h"
#include "lib_buffer.h"
#include "lib_fs.h"
#include "lib_strsplit.h"
#include "nars_io.h"
#include "nars_term.h"

void
app_handle_operation_action(char *operation_script, char *String);

bool
app_file_exists(char *filename);

char *
app_get_source_from_file(char *scriptFile);

void
app_run_script_file(buffer_t *start_file_buf);

#endif //BUMBLESTACK_SRC_VM_APP_SCRIPTS_H
