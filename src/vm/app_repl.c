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

#include <app.h>
#include "app_repl.h"

//Whether the app is in reply mode


int
app_repl_main()
{
	// repl code
	int rc;
	// repl_opts
	repl_opts.prompt = "bumblestack > ";
	repl_opts.eval_cb = app_repl_eval;
	repl_opts.print_cb = app_repl_print;
	repl_opts.error_cb = app_repl_error;

	// initiate
	repl_session_t *sess = repl_session_new(&repl_opts);

	// start
	rc = repl_session_start(sess);

	// destroy
	repl_session_destroy(sess);

	printf("\n");
	return (-1 == rc || 0 == rc)? 0 : rc;
}



static char *
app_repl_eval (repl_session_t *sess, char *buf) {
	// got nothing
	if (feof(sess->repl_stdin)) {
		sess->rc = 0;
		return NULL;
	}
	// pass any input to the NARS engine
	int io_return = io_process_input(buf);
	if(io_return == INPUT_EXIT){
		sess->rc = 0;
		return repl_session_set_error("System will now exit. Goodbye!");
	}
	if(io_return == INPUT_CONTINUE_WITH_ERROR){
		sess->rc = 1;
		return repl_session_set_error("Invalid command or narsese provided.");
	}
	if(io_return == INPUT_CONTINUE){
		return "Done.";
	}
	if(io_return == INPUT_RESET){
		system_reset();
		return "System has been reset.";
	}
}

static void
app_repl_print (repl_session_t *sess, char *buf) {
	fprintf(sess->repl_stdout, "%s\n", buf);
	repl_loop(sess);
}

static void
app_repl_error (repl_session_t *sess, char *err) {
	fprintf(sess->repl_stderr, "error: '%s'\n", err);
	repl_loop(sess);
}

