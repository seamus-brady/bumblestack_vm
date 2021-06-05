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

#include "fifo.h"

void FIFO_Add(Event *event, FIFO *fifo) {
    //build sequence elements:
    for (int len = 0; len < MAX_SEQUENCE_LEN; len++) {
        //len is 0, just add current event to FIFO on len0 level
        if (len == 0) {
            fifo->array[len][fifo->currentIndex] = *event;
        } else //len>0, so chain previous sequence with length len-1 with new event
        {
            Event *sequence = FIFO_GetNewestSequence(fifo, len - 1);
            if (sequence == NULL || sequence->type == EVENT_TYPE_DELETED) {
                break;
            }
            //printf("occurrence times a=%d, b=%d", ((int) sequence->occurrenceTime),((int) event->occurrenceTime));
            bool success;
            Event new_sequence = Inference_BeliefIntersection(sequence, event, &success);
            fifo->array[len][fifo->currentIndex] = success ? new_sequence : (Event) {0};
        }

    }
    fifo->currentIndex = (fifo->currentIndex + 1) % FIFO_SIZE;
    fifo->itemsAmount = MIN(fifo->itemsAmount + 1, FIFO_SIZE);
}

Event *FIFO_GetKthNewestSequence(FIFO *fifo, int k, int len) {
    if (fifo->itemsAmount == 0 || k >= fifo->itemsAmount) {
        return NULL;
    }
    int index = fifo->currentIndex - 1 - k;
    if (index < 0) {
        index = FIFO_SIZE + index;
    }
    return &fifo->array[len][index];
}

Event *FIFO_GetNewestSequence(FIFO *fifo, int len) {
    return FIFO_GetKthNewestSequence(fifo, 0, len);
}
