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

#ifndef H_FIFO
#define H_FIFO

/////////////////////////////////////
//  First in first out (forgotten) //
/////////////////////////////////////
//A FIFO-like structure for event sequencing, which overwrites
//the oldest task when full on Add

//References//
//----------//
#include "nars_inference.h"
#include "nars_globals.h"
#include "nars_narsese.h"
#include "nars_config.h"

//Data structure//
//--------------//
typedef struct
{
	int itemsAmount;
	int currentIndex;
	Event array[MAX_SEQUENCE_LEN][FIFO_SIZE];
} FIFO;
typedef struct
{
	Event *originalEvent;
	Event projectedEvent;
} FIFO_Query_Result;

//Methods//
//-------//
//Add an event to the FIFO
void
FIFO_Add(Event *event, FIFO *fifo);
//Get the newest element
Event *
FIFO_GetNewestSequence(FIFO *fifo, int len);
//Get the k-th newest FIFO element
Event *
FIFO_GetKthNewestSequence(FIFO *fifo, int k, int len);

#endif
