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

#ifndef NARS_EVENT_H
#define NARS_EVENT_H

///////////////////
//   Event       //
///////////////////
//An event named by a term

//References//
//----------//
#include "nars_term.h"
#include "nars_stamp.h"

//Data structure//
//--------------//
#define EVENT_TYPE_GOAL 1
#define EVENT_TYPE_BELIEF 2
#define EVENT_TYPE_DELETED 0
typedef struct
{
	Term term;
	char type; //either JUDGMENT or GOAL
	Truth truth;
	Stamp stamp;
	long occurrenceTime;
	bool processed;
	long creationTime;
	bool isUserKnowledge;
} Event;

//Methods//
//-------//

//Init/Reset module
void
event_init();

//construct an input event
Event
event_input_event(Term term, char type, Truth truth, long currentTime);

//Whether two events are the same
bool
event_equal(Event *event, Event *existing);

#endif
