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

#ifndef H_DECISION
#define H_DECISION

////////////////////
//  NAR Decision  //
////////////////////
//Realization of goals

//References//
//----------//
#include <stdbool.h>
#include <stdio.h>
#include "nars_memory.h"
#include "nars_nar.h"
#include "nars_config.h"

//Parameters//
//----------//
extern double CONDITION_THRESHOLD;
extern double DECISION_THRESHOLD;
extern double ANTICIPATION_THRESHOLD;
extern double ANTICIPATION_CONFIDENCE;
extern double MOTOR_BABBLING_CHANCE;
extern int BABBLING_OPS;

//Data structure//
//--------------//
typedef struct
{
	double desire;
	bool execute;
	int operationID;
	Operation op;
	Term arguments;
	bool specialized;
	Event *reason;
} Decision;

//Methods//
//-------//

//execute decision
void
decision_execute(Decision *decision);

//assumption of failure, also works for "do nothing operator"
void
decision_anticipate(int operationID, long currentTime);

//NAR decision making rule applying when goal is an operation
Decision
Decision_Suggest(Concept *goalconcept, Event *goal, long currentTime);

#endif
