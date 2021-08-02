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

#ifndef H_GLOBALS
#define H_GLOBALS

//////////////
//  Globals //
//////////////

//References//
//////////////
#include <stdbool.h>
#include <string.h>
#include <ctype.h>


// global callback function
typedef void (*Callback)(char *output[250]);
// global context struct
typedef struct
{
	int max_concepts;
	int max_atoms;
	Callback logging_callback;
	Callback action_callback;
	Callback answer_callback;
} Context;

// global app context
Context g_context;

//Macros//
//////////

//Debug macros, debug printing, ASSERT:
#define IS_SYSTEM_IN_DEBUG_MODE(x) {if(DEBUG_MODE){ x } }

//ASSERT, printing message and exiting if b=false
void
globals_assert(bool b, char *message);

// a soft assert for checking input
bool
globals_soft_assert(bool b, char *message);

#define ASSERT globals_assert

#define MIN(a, b) (((a) < (b)) ? (a) : (b))

#define MAX(a, b) (((a) > (b)) ? (a) : (b))

//Number of elements of compile time allocated array:
#define NUM_ELEMENTS(array) (sizeof(array)/sizeof(array[0]))

//Generic hash function on byte array
#define HASH_TYPE long

HASH_TYPE
globals_hash(HASH_TYPE *data, int pieces);

//Random number generator for reproducibility across platforms
int
globals_next_rand(void);

void
globals_sys_rand(unsigned int seed);

#define MY_RAND_MAX 32767

#endif
