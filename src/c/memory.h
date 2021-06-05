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

#ifndef H_MEMORY
#define H_MEMORY

/////////////////
//  NAR Memory //
/////////////////
//The concept-based memory of NAR

//References//
//////////////
#include <math.h>
#include "concept.h"
#include "invertedAtomIndex.h"
#include "priorityqueue.h"
#include "config.h"
#include "hashtable.h"
#include "variable.h"

//Parameters//
//----------//
//Inferences per cycle (amount of events from cycling events)
extern double PROPAGATION_THRESHOLD;
extern bool PRINT_DERIVATIONS;
extern bool PRINT_INPUT;
extern double conceptPriorityThreshold;

//Data structure//
//--------------//
typedef void (*Action)(Term);
typedef struct
{
    Term term;
    Action action;
}Operation;
extern bool ontology_handling;
extern Event selectedBeliefs[BELIEF_EVENT_SELECTIONS]; //better to be global
extern double selectedBeliefsPriority[BELIEF_EVENT_SELECTIONS]; //better to be global
extern int beliefsSelectedCnt;
extern Event selectedGoals[GOAL_EVENT_SELECTIONS]; //better to be global
extern double selectedGoalsPriority[GOAL_EVENT_SELECTIONS]; //better to be global
extern int goalsSelectedCnt;
//Concepts in main memory:
extern PriorityQueue concepts;
//cycling events cycling in main memory:
extern PriorityQueue cycling_belief_events;
extern PriorityQueue cycling_goal_events;
//Hashtable of concepts used for fast retrieval of concepts via term:
extern HashTable HTconcepts;
//Input event buffers:
extern FIFO belief_events;
//Registered perations
extern Operation operations[OPERATIONS_MAX];

//Methods//
//-------//
//Init memory
void Memory_INIT();
//Find a concept
Concept *Memory_FindConceptByTerm(Term *term);
//Create a new concept
Concept* Memory_Conceptualize(Term *term, long currentTime);
//Add event to memory
void Memory_AddEvent(Event *event, long currentTime, double priority, double occurrenceTimeOffset, bool input, bool derived, bool readded, bool revised, bool predicted);
void Memory_AddInputEvent(Event *event, double occurrenceTimeOffset, long currentTime);
//Add operation to memory
void Memory_AddOperation(int id, Operation op);
//check if implication is still valid (source concept might be forgotten)
bool Memory_ImplicationValid(Implication *imp);
//Print an event in memory:
void Memory_printAddedEvent(Event *event, double priority, bool input, bool derived, bool revised, bool controlInfo);
//Print an implication in memory:
void Memory_printAddedImplication(Term *implication, Truth *truth, double occurrenceTimeOffset, double priority, bool input, bool revised, bool controlInfo);

#endif
