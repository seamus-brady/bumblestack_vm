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

#ifndef H_MEMORY
#define H_MEMORY

/////////////////
//  NAR Memory //
/////////////////
//The concept-based memory of NAR

//References//
//////////////
#include <math.h>
#include "nars_concept.h"
#include "nars_inverted_atom_index.h"
#include "nars_priority_queue.h"
#include "nars_config.h"
#include "nars_hashtable.h"
#include "nars_variable.h"

//Parameters//
//----------//

//Inferences per cycle (amount of events from cycling events)
extern double PROPAGATION_THRESHOLD;

extern bool PRINT_DERIVATIONS;

extern bool PRINT_INPUT;

extern double g_conceptPriorityThreshold;

//Data structure//
//--------------//
typedef void (*Action)(Term);
typedef struct
{
	Term term;
	Action action;
	char *script[SCRIPT_LEN_MAX];
} Operation;

extern bool g_ontologyHandling;

extern Event g_selectedBeliefs[BELIEF_EVENT_SELECTIONS]; //better to be global

extern double g_selectedBeliefsPriority[BELIEF_EVENT_SELECTIONS]; //better to be global

extern int g_beliefsSelectedCnt;

extern Event g_selectedGoals[GOAL_EVENT_SELECTIONS]; //better to be global

extern double g_selectedGoalsPriority[GOAL_EVENT_SELECTIONS]; //better to be global

extern int g_goalsSelectedCnt;

//Concepts in main memory:
extern PriorityQueue g_concepts;

//cycling events cycling in main memory:
extern PriorityQueue g_cyclingBeliefEvents;
extern PriorityQueue g_cyclingGoalEvents;

//Hashtable of g_concepts used for fast retrieval of g_concepts via term:
extern HashTable g_hashtableConceptsStruct;

//Input event buffers:
extern FIFO g_beliefEvents;

//Registered perations
extern Operation g_operations[OPERATIONS_MAX];

//Methods//
//-------//

//Init memory
void
memory_init();

//Find a concept
Concept *
memory_find_concept_by_term(Term *term);

//Create a new concept
Concept *
memory_conceptualise(Term *term, long currentTime);

//Add event to memory
void
memory_add_event(Event *event,
                 long currentTime,
                 double priority,
                 double occurrenceTimeOffset,
                 bool input,
                 bool derived,
                 bool readded,
                 bool revised,
                 bool predicted);
void
memory_add_input_event(Event *event, double occurrenceTimeOffset, long currentTime);

//Add operation to memory
void
Memory_AddOperation(int id, Operation op);

//check if implication is still valid (source concept might be forgotten)
bool
memory_implication_valid(Implication *imp);

#endif
