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

#ifndef H_APP
#define H_APP
#include <stdbool.h>
#include <stdlib.h>
#include "nars_nar.h"
#include "lib_slog.h"
#include "nars_io.h"
#include "lib_commander.h"
#include <emscripten.h>

void
app_system_init();

// emscripten needs this here :)
int
app_repl_main();

// entry point for cli app
int
main(int argc, char *argv[]);

// main input function
int
app_input(char *input);

#endif