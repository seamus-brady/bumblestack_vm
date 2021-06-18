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
#define JIM_EMBEDDED
#include "jim.h"
#include <assert.h>
/*
 * Program which we want to get executed.
 */
#define JIM_PROGRAM	"if {1 < 2} { MySampleCommand sample }"


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
		nar_init();
		if (!strcmp(argv[1], "shell"))
		{
//			Shell_Start();
		}
	}
	if (inspectionOnExit)
	{
//		Shell_ProcessInput("*g_concepts");
//		Shell_ProcessInput("*g_cyclingBeliefEvents");
//		Shell_ProcessInput("*g_cyclingGoalEvents");
//		Shell_ProcessInput("*stats");
	}
}

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
}

static int
MySampleCommandFunc(Jim_Interp *interp, int argc, Jim_Obj *const *argv)
{
	const char *str;
	int len;

	if (argc != 2) {
		Jim_WrongNumArgs(interp, 1, argv, "string");
		return (JIM_ERR);
	}

	str = Jim_GetString(argv[1], &len);
	assert(str != NULL);
	printf("%s\n", str);

	return (JIM_OK);
}

int
main(int argc, char *argv[])
{
	system_init();
	io_run_diagnostics();

	Jim_Interp *interp;
	int error;

	/* Create an interpreter. */
	interp = Jim_CreateInterp();
	assert(interp != NULL && "couldn't create interpreter");

	/* We register base commands, so that we actually implement Tcl. */
	Jim_RegisterCoreCommands(interp);

	/* And initialise any static extensions */
	Jim_InitStaticExtensions(interp);

	/* Register our Jim commands. */
	Jim_CreateCommand(interp, "MySampleCommand", MySampleCommandFunc,
	                  NULL, NULL);

	/* Run a script. */
	error = Jim_Eval(interp, JIM_PROGRAM);
	if (error == JIM_ERR) {
		Jim_MakeErrorMessage(interp);
		fprintf(stderr, "%s\n", Jim_GetString(Jim_GetResult(interp), NULL));
		Jim_FreeInterp(interp);
		exit(EXIT_FAILURE);
	}

	Jim_FreeInterp(interp);
	return 0;
}

