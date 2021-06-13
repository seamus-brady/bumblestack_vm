/*
 * Copyright 2021 seamus@bumblestack.com, Corvideon Limited.

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
#include "app_script_loader.h"
#include "lib_slog.h"

static void
writeFn(WrenVM *vm, const char *text)
{
	printf("%s", text);
}

static void
errorFn(WrenVM *vm, WrenErrorType errorType,
        const char *module, const int line,
        const char *msg)
{
	switch (errorType)
	{
		case WREN_ERROR_COMPILE:
		{
			printf("[%s line %d] [Error] %s\n", module, line, msg);
		}
			break;
		case WREN_ERROR_STACK_TRACE:
		{
			printf("[%s line %d] in %s\n", module, line, msg);
		}
			break;
		case WREN_ERROR_RUNTIME:
		{
			printf("[Runtime Error] %s\n", msg);
		}
			break;
	}
}

void
run_script_old(WrenVM *vm)
{
	// ensure right number of slots
	wrenEnsureSlots(vm, 0);
	// set main class
	wrenGetVariable(vm, "main", "BumbleEngine", 0);
	WrenHandle *bumbleEngine = wrenGetSlotHandle(vm, 0);

	// set up function
	WrenHandle *updateFn = wrenMakeCallHandle(vm, "update(_)");
	// call function
	wrenEnsureSlots(vm, 2);
	wrenSetSlotHandle(vm, 0, bumbleEngine);
	wrenSetSlotDouble(vm, 1, 1); // elapsedTime
	wrenCall(vm, updateFn);
	int result = wrenGetSlotDouble(vm, 0);
	printf("Result from Wren: %d\n", result);
	// Release this handle if it finished successfully
	wrenReleaseHandle(vm, updateFn);
	wrenReleaseHandle(vm, bumbleEngine);
}

void
run_script(WrenVM *vm)
{
// ensure right number of slots
wrenEnsureSlots(vm, 0);
// set main class
wrenGetVariable(vm, "main", "BumbleVM", 0);
WrenHandle *jsonParser = wrenGetSlotHandle(vm, 0);

// set up function
WrenHandle *updateFn = wrenMakeCallHandle(vm, "jsonPrint(_)");
// call function
wrenEnsureSlots(vm, 2);
wrenSetSlotHandle(vm, 0, jsonParser);
wrenSetSlotString(vm, 1, "\"lonely string\""); // elapsedTime
wrenCall(vm, updateFn);
// char *result = wrenGetSlotString(vm, 0);
//printf("Result from Wren: %d\n", result);
// Release this handle if it finished successfully
wrenReleaseHandle(vm, updateFn);
wrenReleaseHandle(vm, jsonParser);
}

static const char* coreModuleSource = "class BumbleEngine {\n"
                                      "    static update(elapsedTime){\n"
                                      "         System.print (elapsedTime + 42)\n"
                                      "         return 5.0\n"
                                      "    }\n"
                                      "    static getTestString(){\n"
                                      "         return \"Hello from BumbleEngine!\"\n"
                                      "    }\n"
                                      "}";

void
start_wren()
{
	// init vm
	WrenConfiguration config;
	wrenInitConfiguration(&config);
	config.writeFn = writeFn;
	config.errorFn = errorFn;
	WrenVM *vm = wrenNewVM(&config);
	// load the source
	WrenInterpretResult interpreterResult = wrenInterpret(vm, "main", jsonModuleSource);
	if (interpreterResult != WREN_RESULT_SUCCESS)
	{
		slog_fatal("Wren VM failed to load startup script. This is a fatal error.");
	}
	run_script(vm);
}