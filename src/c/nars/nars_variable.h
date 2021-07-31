/* 
 * The MIT License
 *
 * Copyright 2020 The OpenNARS authors.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
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
#include "nars_narsese.h"

//Data structure//
//--------------//
//Substitution, mapping variable atoms to terms
typedef struct
{
	Term map[27 + 1]; //there can only be 27 variables: $1 to $9 and #1 to #9 and ?1 to ?9, but it can't be 0
	bool success;
} Substitution;

//Methods//
//-------//

//Whether the atom is an independent variable, $i
bool
variable_is_independent_variable(Atom atom);

//Whether the atom is a dependent variable, #1
bool
variable_is_dependent_variable(Atom atom);

//Whether the atom is a query variable, ?1
bool
variable_is_query_variable(Atom atom);

//Whether the atom is any variable
bool
variable_is_variable(Atom atom);

//Whether the term has variables of certain kind
bool
variable_has_variable(Term *term, bool independent, bool dependent, bool query);

//Unify two terms, returning the substitution/unifier
Substitution
variable_unify(Term *general, Term *specific);

Substitution
variable_unify2(Term *general, Term *specific, bool unifyQueryVarOnly);

//Applying the substitution to a term, returning success
Term
variable_apply_substitute(Term term, Substitution substitution, bool *success);

//Introduce variables in an implication
Term
variable_introduce_implication_variables(Term implication, bool *success, bool extensionally);

//Normalize variables, transforming ?what to ?1 for instance.
void
variable_normalize(Term *term);

#endif
