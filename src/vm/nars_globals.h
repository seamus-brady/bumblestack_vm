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

#ifndef H_GLOBALS
#define H_GLOBALS

//////////////
//  Globals //
//////////////

//References//
//////////////
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

//Macros//
//////////
//Whether debug mode should be on
#define DEBUG_MODE false
//Whether control information should be printed - leave as debug mode for now
#define PRINT_CONTROL_INFO DEBUG_MODE
//Priority threshold for printing derivations  - leave as debug mode for now
#define PRINT_DERIVATIONS_PRIORITY_THRESHOLD 0.0
//Debug macros, debug printing, assert:
#define IS_SYSTEM_IN_DEBUG_MODE(x) {if(DEBUG_MODE){ x } }

//assert, printing message and exiting if b=false
void
Globals_Assert(bool b, char *message);

#define assert Globals_Assert
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
//Number of elements of compile time allocated array:
#define NUM_ELEMENTS(array) (sizeof(array)/sizeof(array[0]))
//Generic hash function on byte array
#define HASH_TYPE long

HASH_TYPE
Globals_Hash(HASH_TYPE *data, int pieces);

//Random number generator for reproducibility across platforms
int
myrand(void);

void
mysrand(unsigned int seed);

#define MY_RAND_MAX 32767

#endif
