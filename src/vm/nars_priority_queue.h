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

#ifndef H_PRIORITYQUEUE
#define H_PRIORITYQUEUE

/////////////////////
//  Priority queue //
/////////////////////
//The priority queue for concepts and tasks
//Related publication: Atkinson, M. D., Sack, J. R., Santoro, N., & Strothotte, T. (1986). Min-max heaps and generalized priority queues. Communications of the ACM, 29(10), 996-1000.
//Ported from https://github.com/quxiaofeng/python-stl/blob/master/meshlab/MeshLabSrc_AllInc_v132/meshlab/src/plugins_experimental/edit_ocme/src/cache/old/mmheap.h

//References//
//----------//
#include <stdlib.h>
#include <stdbool.h>

//Data structure//
//--------------//
typedef struct
{
	double priority;
	void *address;
} Item;
typedef struct
{
	Item *items;
	int itemsAmount;
	int maxElements;
} PriorityQueue;
typedef struct
{
	bool added;
	Item addedItem;
	bool evicted;
	Item evictedItem;
} PriorityQueue_Push_Feedback;

//Methods//
//-------//
//Resets the priority queue
void
PriorityQueue_INIT(PriorityQueue *queue, Item *items, int maxElements);
//Push element of a certain priority into the queue.
//If successful, addedItem will point to the item in the data structure, with address of the evicted item, if eviction happened
PriorityQueue_Push_Feedback
PriorityQueue_Push(PriorityQueue *queue, double priority);
//use this function and add again if maybe lower!
bool
PriorityQueue_PopAt(PriorityQueue *queue, int i, void **returnItemAddress);
//Rebuilds the data structure by re-inserting all elements:
void
PriorityQueue_Rebuild(PriorityQueue *queue);
//Pops minimum element
bool
PriorityQueue_PopMin(PriorityQueue *queue, void **returnItemAddress, double *returnItemPriority);
//Pops maximum element
bool
PriorityQueue_PopMax(PriorityQueue *queue, void **returnItemAddress, double *returnItemPriority);

#endif

