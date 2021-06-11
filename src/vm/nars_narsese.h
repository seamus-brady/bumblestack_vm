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

#ifndef H_NARSESE
#define H_NARSESE

/////////////////////
// Narsese encoder //
/////////////////////
//Supports converting Narsese strings to compound terms
//and dictates the format of the internal compound term encoding

//References//
//----------//
#include <string.h>
#include <stdio.h>
#include "nars_term.h"
#include "nars_globals.h"
#include "nars_config.h"

//Data structure//
//--------------//
//Atomic term names:
extern char Narsese_atomNames[ATOMS_MAX][ATOMIC_TERM_LEN_MAX];
extern char Narsese_operatorNames[OPERATIONS_MAX][ATOMIC_TERM_LEN_MAX];
extern Atom SELF;
#define Narsese_RuleTableVars "ABCMRSPXYZ"
#define Naresese_CanonicalCopulas "@*&|;:=$'\"/\\.-%#~+!"

//Methods//
//-------//
//Initializes encoder
void
Narsese_INIT();
//Expands Narsese into by strtok(str," ") tokenizable string with canonical copulas
char *
Narsese_Expand(char *narsese);
//Tokenize expanded Narsese in prefix copula order
char **
Narsese_PrefixTransform(char *narsese_expanded);
//Parses a Narsese string to a compound term
Term
Narsese_Term(char *narsese);
//Parses a Narsese string to a compound term and a tv, tv is default if not present
void
Narsese_Sentence(char *narsese,
                 Term *destTerm,
                 char *punctuation,
                 int *tense,
                 bool *isUserKnowledge,
                 Truth *destTv,
                 double *occurrenceTimeOffset);
//Encodes a sequence
Term
Narsese_Sequence(Term *a, Term *b, bool *success);
//Parses an atomic term string to a term
Term
Narsese_AtomicTerm(char *name);
//Index of atomic term
int
Narsese_AtomicTermIndex(char *name);
//Index of operator
int
Narsese_OperatorIndex(char *name);
//Print an atom
void
Narsese_PrintAtom(Atom atom);
//Print a term
void
Narsese_PrintTerm(Term *term);
//Whether it is a certain copula:
bool
Narsese_copulaEquals(Atom atom, char name);
//Whether it is an operator
bool
Narsese_isOperator(Atom atom);
//Get operator id
int
Narsese_getOperationID(Term *term);
//Is an operation
bool
Narsese_isOperation(Term *term);
//Get precondition without operation
Term
Narsese_GetPreconditionWithoutOp(Term *precondition);
//Get whether something is a true atom, not a copula
bool
Narsese_IsNonCopulaAtom(Atom atom);
//Whether two Narsese strings are equal
bool
Narsese_StringEqual(char *name1, char *name2);
//The hash code of a string
HASH_TYPE
Narsese_StringHash(char *name);
//Whether something is a simple atom such as "cat"
bool
Narsese_IsSimpleAtom(Atom atom);

#endif
