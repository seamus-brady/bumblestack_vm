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

#ifndef H_NAR
#define H_NAR

//////////////////////////////
//  NAR - Yet Another NARS  //
//////////////////////////////

//References//
//-----------//
#include "nars_cycle.h"
#include "nars_narsese.h"
#include "nars_config.h"

//Parameters//
//----------//
#define NAR_DEFAULT_TRUTH ((Truth) { .frequency = NAR_DEFAULT_FREQUENCY, .confidence = NAR_DEFAULT_CONFIDENCE })
extern long g_currentTime;

//Callback function types//
//-----------------------//
//typedef void (*Action)(void);     //already defined in Memory

//Methods//
//-------//
//Init/Reset system
void
NAR_INIT();
//Run the system for a certain amount of cycles
void
NAR_Cycles(int cycles);
//Add input
Event
NAR_AddInput(Term term, char type, Truth truth, bool eternal, double occurrenceTimeOffset, bool isUserKnowledge);
Event
NAR_AddInputBelief(Term term);
Event
NAR_AddInputGoal(Term term);
//Add an operation
void
NAR_AddOperation(Term term, Action procedure);
//Add an Narsese sentence:
void
NAR_AddInputNarsese(char *narsese_sentence);

#endif
