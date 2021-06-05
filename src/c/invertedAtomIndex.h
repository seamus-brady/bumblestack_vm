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

#ifndef H_INVERTEDATOMINDEX
#define H_INVERTEDATOMINDEX

///////////////////////////
//  Inverted atom table  //
///////////////////////////
//The inverted atom table for efficient query

//References//
//////////////
#include "concept.h"
#include "stack.h"
#include "config.h"

//Data structure//
//--------------//
typedef struct
{
    Concept *c;
    void *next;
}ConceptChainElement;
extern ConceptChainElement* conceptChainElementStoragePointers[UNIFICATION_DEPTH*CONCEPTS_MAX];
extern ConceptChainElement conceptChainElementStorage[UNIFICATION_DEPTH*CONCEPTS_MAX];
extern Stack conceptChainElementStack;
extern ConceptChainElement *invertedAtomIndex[ATOMS_MAX];

//Methods//
//-------//
//Init inverted atom index
void InvertedAtomIndex_INIT();
//Add concept to inverted atom index
void InvertedAtomIndex_AddConcept(Term term, Concept *c);
//Remove concept from inverted atom index
void InvertedAtomIndex_RemoveConcept(Term term, Concept *c);
//Print the inverted atom index
void invertedAtomIndexPrint();
//Get the invtable chain with the concepts for an atom
ConceptChainElement* InvertedAtomIndex_GetConceptChain(Atom atom);

#endif
