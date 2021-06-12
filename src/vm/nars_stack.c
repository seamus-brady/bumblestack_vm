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

#include "nars_stack.h"

void
stack_init(Stack *stack, void **items, int maxElements)
{
	stack->stackpointer = 0;
	stack->items = items;
	stack->maxElements = maxElements;
}

void
stack_push(Stack *stack, void *item)
{
	stack->items[stack->stackpointer] = item;
	stack->stackpointer++;
	ASSERT(stack->stackpointer <= stack->maxElements, "VMEntry stack overflow");
}

void *
stack_pop(Stack *stack)
{
	stack->stackpointer--;
	ASSERT(stack->stackpointer >= 0, "VMEntry stack underflow");
	return stack->items[stack->stackpointer];
}

bool
stack_is_empty(Stack *stack)
{
	return stack->stackpointer == 0;
}

