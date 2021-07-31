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

#ifndef H_NARSESE
#define H_NARSESE

/////////////////////
// Narsese encoder //
/////////////////////
//Supports converting Narsese strings to compound terms
//and dictates the format of the internal compound term encoding

//References//
//----------//
#include "app_config.h"
#include "lib/lib_buffer.h"
#include "nars_globals.h"
#include "nars_term.h"
#include <stdio.h>
#include <string.h>

//Data structure//
//--------------//

//Atomic term names:
extern char g_narsese_atomNames[ATOMS_MAX][ATOMIC_TERM_LEN_MAX];
extern char g_narsese_operatorNames[OPERATIONS_MAX][ATOMIC_TERM_LEN_MAX];
extern Atom g_Self;

#define NARSESE_RULE_TABLE_VARIABLES "ABCMRSPXYZ"
#define NARSESE_CANONICAL_COPULAS "@*&|;:=$'\"/\\.-%#~+!"

//Methods//
//-------//

//Initializes encoder
void
narsese_init();

//Expands Narsese into by strtok(str," ") tokenizable string with canonical copulas
char *
narsese_expand(char *narsese);

//Tokenize expanded Narsese in prefix copula order
char **
narsese_prefix_transform(char *narsese_expanded);

//Parses a Narsese string to a compound term
Term
narsese_term(char *narsese);

//Parses a Narsese string to a compound term and a tv, tv is default if not present
void
narsese_get_sentence(char *narsese,
                     Term *destTerm,
                     char *punctuation,
                     int *tense,
                     bool *isUserKnowledge,
                     Truth *destTv,
                     double *occurrenceTimeOffset);

//Encodes a sequence
Term
narsese_sequence(Term *a, Term *b, bool *success);

//Parses an atomic term string to a term
Term
narsese_atomic_term(char *name);

//Index of atomic term
int
narsese_atomic_term_index(char *name);

// check input narsese is valid
bool
narsese_check_sentence_is_valid(char *narsese, char *punctuation, int *tense, bool *isUserKnowledge);

//Index of operator
int
narsese_operator_index(char *name);


//Whether it is a certain copula:
bool
narsese_copula_equals(Atom atom, char name);

//Whether it is an operator
bool
narsese_is_operator(Atom atom);

//Get operator id
int
narsese_get_operation_id(Term *term);

//Is an operation
bool
narsese_is_operation(Term *term);

//Get precondition without operation
Term
narsese_get_precondition_without_op(Term *precondition);

//Get whether something is a true atom, not a copula
bool
narsese_is_non_copula_atom(Atom atom);

//Whether two Narsese strings are equal
bool
narsese_string_equal(char *name1, char *name2);

//The hash code of a string
HASH_TYPE
narsese_string_hash(char *name);

//Whether something is a simple atom such as "cat"
bool
narsese_is_simple_atom(Atom atom);

#endif
