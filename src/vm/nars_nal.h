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

#ifndef H_NAL
#define H_NAL

///////////////////
// NAL ecosystem //
///////////////////
//Declarative reasoning abilities not covered by the sensorimotor component

//References//
//----------//
#include "nars_truth.h"
#include "nars_stamp.h"
#include "nars_narsese.h"
#include "nars_memory.h"

//Methods//
//-------//
//Generates inference rule code
void
nal_generate_rule_table();
//Method for the derivation of new events as called by the generated rule table
void
nal_derived_event(Term conclusionTerm,
                  long conclusionOccurrence,
                  Truth conclusionTruth,
                  Stamp stamp,
                  long currentTime,
                  double parentPriority,
                  double conceptPriority,
                  double occurrenceTimeOffset,
                  Concept *validation_concept,
                  long validation_cid);

//macro for syntactic representation, increases readability, double premise inference
#define R2(premise1, premise2, _, conclusion, truthFunction) nal_generate_rule(#premise1, #premise2, #conclusion, #truthFunction, true,false); nal_generate_rule(#premise2, #premise1, #conclusion, #truthFunction, true, true);

//macro for syntactic representation, increases readability, single premise inference
#define R1(premise1, _, conclusion, truthFunction) nal_generate_rule(#premise1, NULL, #conclusion, #truthFunction, false, false);

//macro for bidirectional transformation rules
#define RTrans(rep1, _, rep2, truthFunction) nal_generate_rule(#rep1, NULL, #rep2, #truthFunction, false, false); nal_generate_rule(#rep2, NULL, #rep1, #truthFunction, false, false);

//macro for term reductions
#define ReduceTerm(pattern, replacement) nal_generate_reduction("(" #pattern " --> M) ", "(" #replacement " --> M)"); nal_generate_reduction("(M --> " #pattern ")", "(M --> " #replacement ")");

//macro for statement reductions
#define ReduceStatement(pattern, replacement) nal_generate_reduction(#pattern, #replacement);

#endif

//Inference rules//
//---------------//
#ifdef H_NAL_RULES

//NAL1 rules
R2( (S --> M), (M --> P), |-, (S --> P), Truth_Deduction )
R2( (A --> B), (A --> C), |-, (C --> B), Truth_Induction )
R2( (A --> C), (B --> C), |-, (B --> A), Truth_Abduction )
R2( (A --> B), (B --> C), |-, (C --> A), Truth_Exemplification )

//NAL2 rules
R1( (S <-> P), |-, (P <-> S), Truth_StructuralDeduction )
R1( (S --> {P}), |-, (S <-> {P}), Truth_StructuralDeduction )
R1( ([S] --> P), |-, ([S] <-> P), Truth_StructuralDeduction )
R2( (P --> M), (S --> M), |-, (S <-> P), Truth_Comparison )
R2( (M --> P), (M --> S), |-, (S <-> P), Truth_Comparison )
R2( (M --> P), (S <-> M), |-, (S --> P), Truth_Analogy )
R2( (P --> M), (S <-> M), |-, (P --> S), Truth_Analogy )
R2( ({M} --> P), (S <-> M), |-, ({S} --> P), Truth_Analogy )
R2( (P --> [M]), (S <-> M), |-, (P --> [S]), Truth_Analogy )
R2( (M <-> P), (S <-> M), |-, (S <-> P), Truth_Resemblance )
R1( ({A} <-> {B}), |-, (A <-> B), Truth_StructuralDeduction )
R1( ([A] <-> [B]), |-, (A <-> B), Truth_StructuralDeduction )

//NAL3 rules
R1( ({A B} --> M), |-, <{A} --> M>, Truth_StructuralDeduction )
R1( ({A B} --> M), |-, <{B} --> M>, Truth_StructuralDeduction )
R1( (M --> [A B]), |-, <M --> [A]>, Truth_StructuralDeduction )
R1( (M --> [A B]), |-, <M --> [B]>, Truth_StructuralDeduction )
R1( ((S | P) --> M), |-, (S --> M), Truth_StructuralDeduction )
R1( (M --> (S & P)), |-, (M --> S), Truth_StructuralDeduction )
R1( ((S | P) --> M), |-, (P --> M), Truth_StructuralDeduction )
R1( (M --> (S & P)), |-, (M --> P), Truth_StructuralDeduction )
R1( ((A ~ S) --> M), |-, (A --> M), Truth_StructuralDeduction )
R1( (M --> (B - S)), |-, (M --> B), Truth_StructuralDeduction )
R1( ((A ~ S) --> M), |-, (S --> M), Truth_StructuralDeductionNegated )
R1( (M --> (B - S)), |-, (M --> S), Truth_StructuralDeductionNegated )
R2( (P --> M), (S --> M), |-, ((P | S) --> M), Truth_Intersection )
R2( (P --> M), (S --> M), |-, ((P & S) --> M), Truth_Union )
R2( (P --> M), (S --> M), |-, ((P ~ S) --> M), Truth_Difference )
R2( (M --> P), (M --> S), |-, (M --> (P & S)), Truth_Intersection )
R2( (M --> P), (M --> S), |-, (M --> (P | S)), Truth_Union )
R2( (M --> P), (M --> S), |-, (M --> (P - S)), Truth_Difference )
R2( (S --> M), ((S | P) --> M), |-, (P --> M), Truth_DecomposePNN )
R2( (P --> M), ((S | P) --> M), |-, (S --> M), Truth_DecomposePNN )
R2( (S --> M), ((S & P) --> M), |-, (P --> M), Truth_DecomposeNPP )
R2( (P --> M), ((S & P) --> M), |-, (S --> M), Truth_DecomposeNPP )
R2( (S --> M), ((S ~ P) --> M), |-, (P --> M), Truth_DecomposePNP )
R2( (S --> M), ((P ~ S) --> M), |-, (P --> M), Truth_DecomposeNNN )
R2( (M --> S), (M --> (S & P)), |-, (M --> P), Truth_DecomposePNN )
R2( (M --> P), (M --> (S & P)), |-, (M --> S), truth_decompose_pnn )
R2( (M --> S), (M --> (S | P)), |-, (M --> P), Truth_DecomposeNPP )
R2( (M --> P), (M --> (S | P)), |-, (M --> S), Truth_DecomposeNPP )
R2( (M --> S), (M --> (S - P)), |-, (M --> P), Truth_DecomposePNP )
R2( (M --> S), (M --> (P - S)), |-, (M --> P), truth_decompose_nnn )

//NAL4 rules
RTrans( ((A * B) --> R), -|-, (A --> (R /1 B)), Truth_StructuralDeduction )
RTrans( ((A * B) --> R), -|-, (B --> (R /2 A)), Truth_StructuralDeduction )
RTrans( (R --> (A * B)), -|-, ((R \\1 B) --> A), Truth_StructuralDeduction )
RTrans( (R --> (A * B)), -|-, ((R \\2 A) --> B), Truth_StructuralDeduction )

//NAL5 rules
R1( (! A), |-, A, Truth_Negation )
R1( (A && B), |-, A, Truth_StructuralDeduction )
R1( (A && B), |-, B, Truth_StructuralDeduction )

//Other NAL5/6/7/8 temporal induction and conditional inference is handled by sensorimotor inference, see Inference.h!

#endif

#ifdef H_NAL_REDUCTIONS

//Extensional intersection, union, conjunction
ReduceTerm( (A & A), A )
ReduceTerm( (A | A), A )
ReduceStatement( (A && A), A )
//Extensional set
ReduceTerm( ({A} | {B}), {A B} )
//Intensional set
ReduceTerm( ([A] & [B]), [A B] )
//Reduce for set element copula
ReduceTerm( {(A . B)}, {A B} )
ReduceTerm( [(A . B)], [A B] )

#endif
