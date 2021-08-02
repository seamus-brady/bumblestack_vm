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
#include "lib/lib_slog.h"
#include "nars/nars_io.h"
#include "nars/nars_nar.h"
#include <stdbool.h>
#include <stdlib.h>
#include "nars/nars_globals.h"

void
app_system_init();

// entry point for lib
void
initialise_bumble(
    void (*logging_callback)(),
    void (*action_callback)(),
    void (*answer_callback)(),
    int max_concepts,
    int max_atoms);

// exit point for lib
int
quit_bumble();

// main input function
int
app_input(char *input);

#endif