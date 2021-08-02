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


int
app_input(char *input){
	return io_process_input(input);
}

void
initialise_bumble(
    void (*logging_callback)(),
    void (*action_callback)(),
    void (*answer_callback)(),
    int max_concepts,
    int max_atoms)
{
	g_context.logging_callback = logging_callback;
	g_context.action_callback = action_callback;
	g_context.answer_callback = answer_callback;
	g_context.max_concepts = max_concepts;
	g_context.max_atoms = max_atoms;
	// boot the system
	app_system_init();
}

int
quit_bumble()
{
	slog_info("System exiting.");
	exit(0);
}



