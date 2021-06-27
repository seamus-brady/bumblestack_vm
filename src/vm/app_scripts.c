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

void
app_handle_javascript_output(char *output)
{
#ifdef WASM_ONLY_FUNCTIONALITY_ENABLED
	// build a string
	buffer_t *buf_output = buffer_new();
	buffer_append(buf_output, JAVASCRIPT_OUTPUT_HANDLER);
	buffer_append(buf_output, "('");
	buffer_append(buf_output, output);
	buffer_append(buf_output, "');");
	slog_info("Calling JavaScript output handler with '%s'", buffer_string(buf_output));
	// run a script in wasm
	emscripten_run_script(buffer_string(buf_output));
	buffer_free(buf_output);
#endif
}

bool
app_file_exists(char *filename)
{
	return (fs_stat(filename) != NULL);
}


char *
app_get_source_from_file(char *scriptFile)
{
	if (app_file_exists(scriptFile))
	{
		return fs_read(scriptFile);
	}
	else
	{
		slog_error("Bad file path provided!");
	}
}

void
app_run_script_file(buffer_t *start_file_buf)
{
	slog_info("Processing data from supplied file...");
	char *mainSource = app_get_source_from_file(buffer_string(start_file_buf));
	char *lines[MAX_SCRIPT_FILE_LINES];
	size_t size = strsplit(mainSource, lines, "\n");
	int i = 0;
	// run the script file line by line
	for (; i < size; ++i) {
		io_process_input( lines[i]);
	}
	slog_info("Completed processing supplied file.");
}