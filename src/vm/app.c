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
bool g_load_file = false;
bool g_load_file_start_repl = false;
buffer_t *g_start_file_buf = NULL;

void
app_system_init()
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
	//TODO - is this a correct default?
	PRINT_DERIVATIONS = false;
}

static void
app_start_repl_command(command_t *self)
{
	g_start_repl = true;
}

static void
app_load_file_command(command_t *self)
{
	g_load_file = true;
	g_start_file_buf = buffer_new();
	buffer_append(g_start_file_buf, self->arg);
}

static void
app_load_file_repl_command(command_t *self)
{
	g_load_file_start_repl = true;
	g_start_file_buf = buffer_new();
	buffer_append(g_start_file_buf, self->arg);
}

int
app_input(char *input){
	return io_process_input(input);
}

int
main(int argc, char *argv[])
{
	command_t cmd;
	command_init(&cmd, argv[0], "0.0.1");
	command_option(&cmd, "-r", "--repl", "start the BumbleStack repl", app_start_repl_command);
	command_option(&cmd, "-f", "--file [arg]", "load data from a file path", app_load_file_command);
	command_option(&cmd,
	               "-b",
	               "--background [arg]",
	               "load background setup from a file, then start the repl",
	               app_load_file_repl_command);
	command_parse(&cmd, argc, argv);
	command_free(&cmd);
	// boot the system
	app_system_init();
	// process the args
	if (g_start_repl)
	{
		// repl now become the main loop if the arg was passed in
		slog_info("Starting the BumbleStack repl...");
		app_repl_main();
		slog_info("BumbleStack exited.");
	}
	if (g_load_file)
	{
		app_run_script_file(g_start_file_buf);
	}
	if (g_load_file_start_repl)
	{
		app_run_script_file(g_start_file_buf);
		slog_info("Starting the BumbleStack repl...");
		app_repl_main();
		slog_info("BumbleStack exited.");
	}
	exit(0);
}

