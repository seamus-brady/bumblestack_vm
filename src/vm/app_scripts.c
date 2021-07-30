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

// gets rid of newlines
void chomp(char *s) {
	int len = strlen(s);
	if( s[len-1] == '\n' )
		s[len-1] = 0;
}

void
app_handle_operation_action(char *term_string, char *script)
{
	slog_info("Running operation defined by term: %s", term_string);
	slog_info("Operation has a script attached: %s", script);
	// the output below can be picked up by an external script
	slog_action(script);
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
	for (; i < size; ++i)
	{
		io_process_input(lines[i]);
	}
	slog_info("Completed processing supplied file.");
}