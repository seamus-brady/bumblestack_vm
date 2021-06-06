/* 
 * Copyright 2021 seamus@bumblestack.com, Corvideon Limited.
 * Portions of this code were originally created by the OpenNARS authors under the MIT License.

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

void Process_Args(int argc, char *argv[]) {
    bool inspectionOnExit = false;
    long iterations = -1;
    if (argc >= 4) {
        if (!strcmp(argv[3], "InspectionOnExit")) {
            inspectionOnExit = true;
        }
    }
    if (argc >= 3) {
        if (!strcmp(argv[2], "InspectionOnExit")) {
            inspectionOnExit = true;
        }
    }
    if (argc >= 2) {
        NAR_INIT();
        if (!strcmp(argv[1], "shell")) {
            Shell_Start();
        }
    }
    if (inspectionOnExit) {
        Shell_ProcessInput("*concepts");
        Shell_ProcessInput("*cycling_belief_events");
        Shell_ProcessInput("*cycling_goal_events");
        Shell_ProcessInput("*stats");
    }
}



void systemInit(){
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

static void writeFn(WrenVM* vm, const char* text)
{
    printf("%s", text);
}

void errorFn(WrenVM* vm, WrenErrorType errorType,
             const char* module, const int line,
             const char* msg)
{
    switch (errorType)
    {
        case WREN_ERROR_COMPILE:
        {
            printf("[%s line %d] [Error] %s\n", module, line, msg);
        } break;
        case WREN_ERROR_STACK_TRACE:
        {
            printf("[%s line %d] in %s\n", module, line, msg);
        } break;
        case WREN_ERROR_RUNTIME:
        {
            printf("[Runtime Error] %s\n", msg);
        } break;
    }
}

EMSCRIPTEN_KEEPALIVE
int main(int argc, char *argv[]) {
    systemInit();
    WrenConfiguration config;
    wrenInitConfiguration(&config);
    config.writeFn = &writeFn;
    config.errorFn = &errorFn;
    WrenVM* vm = wrenNewVM(&config);

    const char* module = "main";
    const char* script = "System.print(\"I am running in a VM!\")";

    WrenInterpretResult result = wrenInterpret(vm, module, script);

    switch (result)
    {
        case WREN_RESULT_COMPILE_ERROR:
        { printf("Compile Error!\n"); } break;
        case WREN_RESULT_RUNTIME_ERROR:
        { printf("Runtime Error!\n"); } break;
        case WREN_RESULT_SUCCESS:
        { printf("Success!\n"); } break;
    }

    wrenFreeVM(vm);
    return 0;
}

