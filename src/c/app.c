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

// error reporting callback called by both compiler or VM
static void report_error (gravity_vm *vm, error_type_t error_type,
                          const char *description, error_desc_t error_desc, void *xdata) {
    printf("%s\n", description);
    exit(0);
}

int test_gravity (void) {
    // configure a VM delegate
    gravity_delegate_t delegate = {.error_callback = report_error};

    // compile Gravity source code into bytecode
    gravity_compiler_t *compiler = gravity_compiler_create(&delegate);
    gravity_closure_t *closure = gravity_compiler_run(compiler, SOURCE, strlen(SOURCE), 0, true, true);

    // sanity check on compiled source
    if (!closure) {
        // an error occurred while compiling source code and it has already been reported by the report_error callback
        gravity_compiler_free(compiler);
        return 1;
    }

    // create a new VM
    gravity_vm *vm = gravity_vm_new(&delegate);

    // transfer objects owned by the compiler to the VM (so they can be part of the GC)
    gravity_compiler_transfer(compiler, vm);

    // compiler can now be freed
    gravity_compiler_free(compiler);

    // run main closure inside Gravity bytecode
    if (gravity_vm_runmain(vm, closure)) {
        // print result (INT) 30 in this simple example
        gravity_value_t result = gravity_vm_result(vm);
        gravity_value_dump(vm, result, NULL, 0);
    }

    // free VM memory and core libraries
    gravity_vm_free(vm);
    gravity_core_free();

    return 0;
}


int main(int argc, char *argv[]) {
    systemInit();
    run_diagnostics();
    test_gravity();
    return 0;
}

