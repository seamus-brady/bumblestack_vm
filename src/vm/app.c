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
#include "app.h"

bool g_start_repl = false;

void
system_init()
{
	// set up random number generator
	globals_sys_rand(SEED);

	// initialise logging
	io_setup_logging();
	slog_info("Welcome to BumbleStack!");

	// initialise the bumblestack NARS system
	nar_init();
	slog_info("System initialised.");

	// set up the shell with feedback
	PRINT_DERIVATIONS = true;
}


static void
app_repl_command(command_t *self) {
	g_start_repl = true;
}

int
main(int argc, char *argv[])
{
	command_t cmd;
	command_init(&cmd, argv[0], "0.0.1");
	command_option(&cmd, "-r", "--repl", "start the BumbleStack repl", app_repl_command);
	command_parse(&cmd, argc, argv);
	command_free(&cmd);
	// boot the system
	system_init();
	// start_wren();
	// repl now become the main loop if the arg was passed in
	if(g_start_repl){
		slog_info("Starting the BumbleStack repl...");
		app_repl_main();
		slog_info("BumbleStack exited.");
	}
	exit(0);
}

