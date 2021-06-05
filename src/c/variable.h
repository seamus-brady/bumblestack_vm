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

#ifndef H_VARIABLE
#define H_VARIABLE

////////////////////////
// Variable utilities //
////////////////////////
//Support for NAL-6 variables

//References//
//----------//
#include "narsese.h"

//Data structure//
//--------------//
//Substitution, mapping variable atoms to terms
typedef struct {
    Term map[27+1]; //there can only be 27 variables: $1 to $9 and #1 to #9 and ?1 to ?9, but it can't be 0
    bool success;
} Substitution;

//Methods//
//-------//
//Whether the atom is an independent variable, $i
bool Variable_isIndependentVariable(Atom atom);
//Whether the atom is a dependent variable, #1
bool Variable_isDependentVariable(Atom atom);
//Whether the atom is a query variable, ?1
bool Variable_isQueryVariable(Atom atom);
//Whether the atom is any variable
bool Variable_isVariable(Atom atom);
//Whether the term has variables of certain kind
bool Variable_hasVariable(Term *term, bool independent, bool dependent, bool query);
//Unify two terms, returning the substitution/unifier
Substitution Variable_Unify(Term *general, Term *specific);
Substitution Variable_Unify2(Term *general, Term *specific, bool unifyQueryVarOnly);
//Applying the substitution to a term, returning success
Term Variable_ApplySubstitute(Term term, Substitution substitution, bool *success);
//Introduce variables in an implication
Term IntroduceImplicationVariables(Term implication, bool *success, bool extensionally);
//Normalize variables, transforming ?what to ?1 for instance.
void Variable_Normalize(Term *term);

#endif
