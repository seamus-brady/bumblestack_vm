/*
 * Copyright 2021 seamus@bumblestack.com, Corvideon Limited.
 * Portions of this code were originally created by the OpenNARS authors under
 the MIT License.

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

buffer_t *scriptPathBuffer = NULL;

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
		Shell_ProcessInput("*concepts");
		Shell_ProcessInput("*cycling_belief_events");
		Shell_ProcessInput("*cycling_goal_events");
		Shell_ProcessInput("*stats");
	}
}

void
systemInit()
{
	// set up random number generator
	mysrand(SEED);

	// initialise logging
	setupLogging();
	slog_info("Welcome to BumbleStack!");

	// initialise the bumblestack NARS system
	NAR_INIT();
	slog_info("System initialised.");
	statsPrint(currentTime);
	printAtomTable();
	printConcepts();
	printCyclingBeliefEvents();
	printCyclingGoalEvents();
}

static void
enableDebugMode() { printf("BumbleVM debug mode: enabled\n"); }

static void
getStartupScript(command_t *self)
{
	printf("Startup script: %s\n", self->arg);
	scriptPathBuffer = buffer_new();
	buffer_append(scriptPathBuffer, self->arg);
}

int
main(int argc, char *argv[])
{
	systemInit();
	command_t cmd;
	command_init(&cmd, argv[0], "0.0.8");
	command_option(&cmd, "-d", "--debug", "Enable BumbleVM debug mode", enableDebugMode);
	command_option(&cmd, "-s", "--startup-script <arg>", "Required startup script", getStartupScript);
	// command_option(&cmd, "-o", "--optional [arg]", "optional arg", optional);
	command_parse(&cmd, argc, argv);
	command_free(&cmd);
	if (scriptPathBuffer != NULL)
	{
		run_script(buffer_string(scriptPathBuffer));
	}
	else
	{
		run_script("./test.wren");
	}

	return 0;
}
