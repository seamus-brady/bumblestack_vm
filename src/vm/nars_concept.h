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

#ifndef H_CONCEPT
#define H_CONCEPT

///////////////////
//   Concept     //
///////////////////
//A concept named by a term

//References//
//-----------//
#include "nars_fifo.h"
#include "nars_table.h"
#include "nars_usage.h"

//Data structure//
//--------------//
typedef struct
{
	long id;
	Usage usage;
	Term term;
	Event belief; //the highest confident eternal belief
	Event belief_spike;
	Event predicted_belief;
	Event goal_spike;
	Table precondition_beliefs[OPERATIONS_MAX + 1];
	double priority;
	bool hasUserKnowledge;
	long processID; //avoids duplicate processing
} Concept;

//Methods//
//-------//
//todo

#endif
