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
Process_Args(int argc, char *argv[])
{
	bool inspectionOnExit = false;
	long iterations = -1;
	if (argc >= 4)
	{
		if (!strcmp(argv[3], "InspectionOnExit"))
		{
			inspectionOnExit = true;
		}
	}
	if (argc >= 3)
	{
		if (!strcmp(argv[2], "InspectionOnExit"))
		{
			inspectionOnExit = true;
		}
	}
	if (argc >= 2)
	{
		NAR_INIT();
		if (!strcmp(argv[1], "shell"))
		{
			Shell_Start();
		}
	}
	if (inspectionOnExit)
	{
		Shell_ProcessInput("*g_concepts");
		Shell_ProcessInput("*g_cyclingBeliefEvents");
		Shell_ProcessInput("*g_cyclingGoalEvents");
		Shell_ProcessInput("*stats");
	}
}

void
systemInit()
{
	// set up random number generator
	globals_sys_rand(SEED);

	// initialise logging
	io_setup_logging();
	slog_info("Welcome to BumbleStack!");

	// initialise the bumblestack NARS system
	NAR_INIT();
	slog_info("System initialised.");
	stats_print(g_currentTime);
	io_print_atom_table();
	io_print_concepts();
	io_print_cycling_belief_events();
	io_print_cycling_goal_events();
}

int
main(int argc, char *argv[])
{
	systemInit();
	io_run_diagnostics();
	start_wren();
	return 0;
}

