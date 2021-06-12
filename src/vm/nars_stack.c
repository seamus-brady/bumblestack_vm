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

#include "nars_stack.h"

void
Stack_INIT(Stack *stack, void **items, int maxElements)
{
	stack->stackpointer = 0;
	stack->items = items;
	stack->maxElements = maxElements;
}

void
Stack_Push(Stack *stack, void *item)
{
	stack->items[stack->stackpointer] = item;
	stack->stackpointer++;
	ASSERT(stack->stackpointer <= stack->maxElements, "VMEntry stack overflow");
}

void *
Stack_Pop(Stack *stack)
{
	stack->stackpointer--;
	ASSERT(stack->stackpointer >= 0, "VMEntry stack underflow");
	return stack->items[stack->stackpointer];
}

bool
Stack_IsEmpty(Stack *stack)
{
	return stack->stackpointer == 0;
}

