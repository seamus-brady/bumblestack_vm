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

#ifndef H_RULETABLE
#define H_RULETABLE

/////////////////
//  RuleTable  //
/////////////////
//The rule table which .vm is generated at compile time
//by NAL_GenerateRuleTable

//References//
//----------//
#include "nars_nal.h"

//Methods//
//-------//
void
RuleTableApply(Term term1,
               Term term2,
               Truth truth1,
               Truth truth2,
               long conclusionOccurrence,
               double occurrenceTimeOffset,
               Stamp conclusionStamp,
               long currentTime,
               double parentPriority,
               double conceptPriority,
               bool doublePremise,
               Concept *validation_concept,
               long validation_cid);
Term
RuleTableReduce(Term term1, bool doublePremise);

#endif
