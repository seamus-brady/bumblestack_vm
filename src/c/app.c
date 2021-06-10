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


void systemInit() {
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

static void writeFn(WrenVM *vm, const char *text) {
    printf("%s", text);
}

void errorFn(WrenVM *vm, WrenErrorType errorType,
             const char *module, const int line,
             const char *msg) {
    switch (errorType) {
        case WREN_ERROR_COMPILE: {
            printf("[%s line %d] [Error] %s\n", module, line, msg);
        }
            break;
        case WREN_ERROR_STACK_TRACE: {
            printf("[%s line %d] in %s\n", module, line, msg);
        }
            break;
        case WREN_ERROR_RUNTIME: {
            printf("[Runtime Error] %s\n", msg);
        }
            break;
    }
}

void runWrenVM() {
    slog_info("Starting WrenVM.");
    WrenConfiguration config;
    wrenInitConfiguration(&config);
    config.writeFn = &writeFn;
    config.errorFn = &errorFn;
    WrenVM *vm = wrenNewVM(&config);

    const char *module = "main";

    const char *script = "System.print(\"I am running in a VM!\")\n\
    class Wren {\n\
            flyTo(city) {\n\
                System.print(\"Flying to %(city)\")\n\
            }\n\
    }\n\
    var adjectives = Fiber.new {\n\
        [\"small\", \"clean\", \"fast\"].each {|word| Fiber.yield(word) }\n\
    }\n\
    while (!adjectives.isDone) System.print(adjectives.call())";

    WrenInterpretResult result = wrenInterpret(vm, module, script);

    switch (result) {
        case WREN_RESULT_COMPILE_ERROR: {
            printf("Compile Error!\n");
        }
            break;
        case WREN_RESULT_RUNTIME_ERROR: {
            printf("Runtime Error!\n");
        }
            break;
        case WREN_RESULT_SUCCESS: {
            printf("Success!\n");
        }
            break;
    }

    wrenFreeVM(vm);
}

const char *testWrenSource = "class BumbleEngine {\n" \
                       "  static update(elapsedTime) {\n" \
                       "     System.print(elapsedTime)\n" \
                       "  }\n" \
                       "}";

void readModuleComplete(WrenVM *vm, const char *module, WrenLoadModuleResult result) {
    if (result.source) {
        free((void *) result.source);
        result.source = NULL;
    }
}

#define SIZE 2048

char * getSourceForModule(char *file_name) {
    FILE *file = fopen(file_name, "r");
    // Check if there was an error.
    if (file == NULL) {
        fprintf(stderr, "Error: Can't open file '%s'.", file_name);
        exit(EXIT_FAILURE);
    }
    // Get the file length
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);
    // Create the string for the file contents.
    char *buffer = malloc(sizeof(char) * (length + 1));
    buffer[length] = '\0';
    // Set the contents of the string.
    fread(buffer, sizeof(char), length, file);
    // Close the file.
    fclose(file);
    return buffer;
}

WrenLoadModuleResult readModule(WrenVM *vm, const char *name) {
    WrenLoadModuleResult result = {0};
    result.source = getSourceForModule(name);
    return result;
}

static WrenVM *initVM() {
    WrenConfiguration config;
    wrenInitConfiguration(&config);
    config.loadModuleFn = readModule;
    config.writeFn = &writeFn;
    config.errorFn = &errorFn;
    return wrenNewVM(&config);
}

int main(int argc, char *argv[]) {
    systemInit();
    // runWrenVM();
    puts(getSourceForModule("/home/seamus/GitHub/bumblestack-repos/bumblestack/src/c/test.wren"));
    WrenConfiguration config;
    wrenInitConfiguration(&config);
    WrenVM *otherVM = wrenNewVM(&config);
    // wrenInterpret(otherVM, "test", testWrenSource);
    // WrenHandle* method = wrenMakeCallHandle(otherVM, "update(_)");
    // wrenEnsureSlots(otherVM, 1);
    // wrenGetVariable(otherVM, "main", "BumbleEngine", 0);
    // WrenHandle* testClass = wrenGetSlotHandle(otherVM, 0);

    wrenEnsureSlots(otherVM, 2);
    wrenGetVariable(otherVM, "/home/seamus/GitHub/bumblestack-repos/bumblestack/src/c/test.wren", "BumbleEngine", 0);
    WrenHandle *method = wrenMakeCallHandle(otherVM, "update(_)");
    // wrenSetSlotHandle(otherVM, 0, testClass);
    wrenSetSlotDouble(otherVM, 1, 42); // elapsedTime
    wrenCall(otherVM, method);
    double result = wrenGetSlotDouble(otherVM, 0);
    printf("Result from Wren: %d", result);
    return 0;
}

