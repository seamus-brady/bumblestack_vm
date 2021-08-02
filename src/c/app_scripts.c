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
app_handle_operation_action(char *op, Term arguments)
{
	slog_info("Running operation defined by op: %s", op);
	// call action callback function
	buffer_t *buf = buffer_new();
	buffer_append(buf, op);
	buffer_append(buf, "; ");
	io_narsese_print_term_with_buffer(&arguments, buf);
	g_context.action_callback(buffer_string(buf));
}

