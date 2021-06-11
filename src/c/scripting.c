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

#include "scripting.h"
#include "slog.h"

char *
getSourceForModule(char *scriptFile)
{
	return fs_read(scriptFile);
}

static void
writeFn(WrenVM *vm, const char *text)
{
	printf("%s", text);
}

void
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
callOne(WrenVM *vm)
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
	wrenSetSlotDouble(vm, 1, 0); // elapsedTime
	wrenCall(vm, updateFn);
	int result = wrenGetSlotDouble(vm, 0);
	printf("Result from Wren: %d\n", result);
	// Release this handle if it finished successfully
	wrenReleaseHandle(vm, updateFn);
	wrenReleaseHandle(vm, bumbleEngine);
}

void
callTwo(WrenVM *vm)
{// ensure right number of slots
	wrenEnsureSlots(vm, 0);
	// set main class
	wrenGetVariable(vm, "main", "BumbleEngine", 0);
	WrenHandle *bumbleEngine = wrenGetSlotHandle(vm, 0);
	// set up function
	WrenHandle *testStringFn = wrenMakeCallHandle(vm, "getTestString()");
	// call function
	wrenEnsureSlots(vm, 1);
	wrenSetSlotHandle(vm, 0, bumbleEngine);
	wrenCall(vm, testStringFn);
	char *resultStr = wrenGetSlotString(vm, 0);
	printf("Result from Wren: %s\n", resultStr);
	// Release this handle if it finished successfully
	wrenReleaseHandle(vm, testStringFn);
	wrenReleaseHandle(vm, bumbleEngine);
}

void
run_script(char *sourceFile)
{
	// get source for module
	char *mainSource = getSourceForModule(sourceFile);
	// init vm
	WrenConfiguration config;
	wrenInitConfiguration(&config);
	config.writeFn = writeFn;
	config.errorFn = errorFn;
	WrenVM *vm = wrenNewVM(&config);
	// load the source
	WrenInterpretResult interpreterResult = wrenInterpret(vm, "main", mainSource);
	free(mainSource);
	if (interpreterResult != WREN_RESULT_SUCCESS)
	{
		slog_fatal("Wren VM failed to load startup script. This is a fatal error.");
	}
	callOne(vm);
	callTwo(vm);
}


