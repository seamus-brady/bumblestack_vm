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
#include "nars_concept.h"
#include "nars_stack.h"
#include "nars_config.h"

//Data structure//
//--------------//
typedef struct
{
	Concept *c;
	void *next;
} ConceptChainElement;

extern ConceptChainElement *g_conceptChainElementStoragePointers[UNIFICATION_DEPTH * CONCEPTS_MAX];

extern ConceptChainElement g_conceptChainElementStorage[UNIFICATION_DEPTH * CONCEPTS_MAX];

extern Stack g_conceptChainElementStack;

extern ConceptChainElement *g_invertedAtomIndex[ATOMS_MAX];

//Methods//
//-------//
//Init inverted atom index
void
inverted_atom_index_init();

//Add concept to inverted atom index
void
inverted_atom_index_add_concept(Term term, Concept *c);

//Remove concept from inverted atom index
void
inverted_atom_index_remove_concept(Term term, Concept *c);

//Print the inverted atom index
void
inverted_atom_index_print();

//Get the invtable chain with the g_concepts for an atom
ConceptChainElement *
inverted_atom_index_get_concept_chain(Atom atom);

#endif
