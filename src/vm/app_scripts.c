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
#include "app_scripts.h"

void
app_handle_operation_action(char *term_string, char *script)
{
	slog_info("Running operation defined by term: %s", term_string);
	slog_info("Operation has a script attached: %s", script);
	// the output below can be picked up by an external script
	slog_action(script);
}

void
app_handle_javascript_operation_action(char *term_string, char *script)
{
#ifdef WASM_ONLY_FUNCTIONALITY_ENABLED
	// build a string
	buffer_t *buf_action = buffer_new();
	buffer_append(buf_action, JAVASCRIPT_ACTION_HANDLER);
	buffer_append(buf_action, "('");
	buffer_append(buf_action, script);
	buffer_append(buf_action, "');");
	slog_info("Calling JavaScript action handler with '%s'", buffer_string(buf_action));
	// run a script in wasm
	emscripten_run_script(buffer_string(buf_action));
	buffer_free(buf_action);
#endif
}
