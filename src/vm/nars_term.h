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

#ifndef H_TERM
#define H_TERM

//////////////
//   Term   //
//////////////

//Description//
//-----------//
//An Term is an blocksay of a specific number of 128 bit blocks
//(that way no Hash ops are necessary, it's faster for this Term size)

//References//
//----------//
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include "nars_truth.h"
#include "nars_config.h"
#include <string.h>

//Data structure//
//--------------//
#define HASH_TYPE_SIZE sizeof(HASH_TYPE)

#define TERM_ATOMS_SIZE (sizeof(Atom)*COMPOUND_TERM_SIZE_MAX)

typedef struct
{
	bool hashed;
	HASH_TYPE hash;
	Atom atoms[COMPOUND_TERM_SIZE_MAX];
} Term;

//Methods//
//-------//
//Whether two Term's are equal completely
bool
term_equal(Term *a, Term *b);

//Overwrites a subterm
bool
term_override_subterm(Term *term, int i, Term *subterm);

//Extract a subterm as a term
Term
term_extract_subterm(Term *term, int j);

//The complexity of a term
int
term_complexity(Term *term);

//Hash of a term (needed by the term->concept HashTable)
HASH_TYPE
term_hash(Term *term);

#endif
