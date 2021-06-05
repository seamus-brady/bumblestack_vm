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

#ifndef H_STACK
#define H_STACK

/////////////
//  Stack  //
/////////////
//The stack for use by the hashtable

//References//
//----------//
#include <stdlib.h>
#include <stdbool.h>
#include "concept.h"

//Data structure//
//--------------//
typedef struct
{
    void** items;
    int stackpointer;
    int maxElements;
} Stack;

//Methods//
//-------//
void Stack_INIT(Stack *stack, void **items, int maxElements);
//Add a VMItem on the top of the stack
void Stack_Push(Stack *stack, void *item);
//Remove a VMItem from the top of the stack
void* Stack_Pop(Stack *stack);
//Check if there aren't VMItems left on the stack
bool Stack_IsEmpty(Stack *stack);

#endif

