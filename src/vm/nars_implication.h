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

#ifndef H_IMPLICATION
#define H_IMPLICATION

//////////////////////
//  Implication     //
//////////////////////
//essentially allowing g_concepts to predict activations of others

//References//
//----------//
#include "nars_term.h"
#include "nars_stamp.h"

//Data structure//
//--------------//
typedef struct
{
	Term term;
	Truth truth;
	Stamp stamp;
	//for deciding occurrence time of conclusion:
	double occurrenceTimeOffset;
	//for efficient spike propagation:
	void *sourceConcept;
	long sourceConceptId; //to check whether it's still the same
	long creationTime;
	bool isUserKnowledge;
} Implication;

#endif


