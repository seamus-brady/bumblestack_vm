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
#include "lib_slog.h"
#include "nars_globals.h"
#include "nars_io.h"
#include "nars_nar.h"
#include <stdbool.h>
#include <stdlib.h>

void
app_system_init();

// entry point for lib
void
app_init_bumble(
    int max_concepts,
    int max_atoms);

// exit point for lib
int
app_quit_bumble();

// main input function
int
app_add_input(char *input);

// main add operation function
void
app_add_operation(char *term_string, Action *action);


#endif