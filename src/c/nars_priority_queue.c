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

#include "nars_priority_queue.h"

#define ITEM_AT(i) (queue->items[i])

void
priority_queue_init(PriorityQueue *queue, Item *items, int maxElements)
{
	queue->items = items;
	queue->maxElements = maxElements;
	queue->itemsAmount = 0;
}

static void
priority_queue_swap(PriorityQueue *queue, int index1, int index2)
{
	Item temp = ITEM_AT(index1);
	ITEM_AT(index1) = ITEM_AT(index2);
	ITEM_AT(index2) = temp;
}

static bool
priority_queue_is_on_max_level(int i)
{
	int level = -1;
	int n = i + 1;
	while (n)
	{
		n = n >> 1;
		level++;
	}
	return level & 1; /*% 2*/;
}

static int
priority_queue_parent(int i)
{
	return ((i + 1) / 2) - 1;
}

static int
priority_queue_grandparent(int i)
{
	return ((i + 1) / 4) - 1;
}

static int
priority_queue_left_child(int i)
{
	return 2 * i + 1;
}

static int
priority_queue_left_grandchild(int i)
{
	return 4 * i + 3;
}

static int
priority_queue_smallest_child(PriorityQueue *queue, int i, bool invert)
{ //return smallest of children or self if no children
	int l = priority_queue_left_child(i);
	if (l >= queue->itemsAmount)
	{
		return i; //no children, return self
	}
	int r = l + 1; //right child
	if (r < queue->itemsAmount)
	{
		Item lv = ITEM_AT(l);
		Item rv = ITEM_AT(r);
		if ((rv.priority < lv.priority) ^ invert)
		{
			return r;
		}
	}
	return l;
}

static int
priority_queue_smallest_grandchild(PriorityQueue *queue, int i, bool invert)
{//return smallest of grandchildren or self if no children
	int l = priority_queue_left_grandchild(i);
	if (l >= queue->itemsAmount)
	{
		return i;
	}
	Item lv = ITEM_AT(l);
	int min = l;
	for (int r = l + 1;
	     r < queue->itemsAmount && r < l + 4; r++)
	{ //iterate on three grandsiblings (they are consecutive)
		Item rv = ITEM_AT(r);
		if ((rv.priority < lv.priority) ^ invert)
		{
			lv = rv;
			min = r;
		}
	}
	return min;
}

void
priority_queue_trickle_down(PriorityQueue *queue, int i, bool invert)
{
	while (1)
	{
		//enforce min-max property on level(i), we need to check children and grandchildren
		int m = priority_queue_smallest_child(queue, i, invert);
		if (m == i)
		{
			break; //no children
		}
		if ((ITEM_AT(m).priority < ITEM_AT(i).priority) ^
			invert) //priority_queue_swap children, max property on level(i)+1 automatically enforced
		{
			priority_queue_swap(queue, i, m);
		}
		int j = priority_queue_smallest_grandchild(queue, i, invert);
		if (j == i)
		{
			break; //no grandchildren
		}
		if ((ITEM_AT(j).priority < ITEM_AT(i).priority) ^ invert)
		{
			priority_queue_swap(queue, i, j);
			i = j; //we need to enforce min-max property on level(j) now.
		}
		else
		{
			break; //no priority_queue_swap, finish
		}
	}
}

void
priority_queue_bubble_up(PriorityQueue *queue, int i)
{
	int m;
	m = priority_queue_parent(i);
	bool invert = priority_queue_is_on_max_level(i);
	if (m >= 0 && ((ITEM_AT(i).priority > ITEM_AT(m).priority) ^ invert))
	{
		priority_queue_swap(queue, i, m);
		i = m;
		invert = !invert;
	}
	m = priority_queue_grandparent(i);
	while (m >= 0 && ((ITEM_AT(i).priority < ITEM_AT(m).priority) ^ invert))
	{
		priority_queue_swap(queue, i, m);
		i = m;
		m = priority_queue_grandparent(i);
	}
}

bool
priority_queue_pop_min(PriorityQueue *queue, void **returnItemAddress, double *returnItemPriority)
{
	if (queue->itemsAmount == 0)
	{
		return false;
	}
	Item item = ITEM_AT(0);
	priority_queue_swap(queue, 0, queue->itemsAmount - 1);
	queue->itemsAmount--;
	priority_queue_trickle_down(queue, 0, false); //enforce minmax heap property
	if (returnItemAddress != NULL)
	{
		*returnItemAddress = item.address;
	}
	if (returnItemPriority != NULL)
	{
		*returnItemPriority = item.priority;
	}
	return true;
}

bool
priority_queue_pop_max(PriorityQueue *queue, void **returnItemAddress, double *returnItemPriority)
{
	if (queue->itemsAmount == 0)
	{
		return false;
	}
	int p = priority_queue_smallest_child(queue, 0, true);
	Item item = ITEM_AT(p);
	priority_queue_swap(queue, p, queue->itemsAmount - 1); //priority_queue_swap max with last item
	queue->itemsAmount--;
	priority_queue_trickle_down(queue, p, true); //enforce minmax heap property
	if (returnItemAddress != NULL)
	{
		*returnItemAddress = item.address;
	}
	if (returnItemPriority != NULL)
	{
		*returnItemPriority = item.priority;
	}
	return true;
}

PriorityQueuePushFeedback
priority_queue_push(PriorityQueue *queue, double priority)
{
	PriorityQueuePushFeedback feedback = (PriorityQueuePushFeedback) {0};
	//first evict if necessary
	if (queue->itemsAmount >= queue->maxElements)
	{
		double minPriority = ITEM_AT(0).priority;
		if (priority < minPriority)
		{ //smaller than smallest
			return feedback;
		}
		feedback.evicted = true;
		feedback.evictedItem.priority = minPriority;
		priority_queue_pop_min(queue, &feedback.evictedItem.address, NULL);
	}
	ITEM_AT(queue->itemsAmount).priority = priority;
	if (feedback.evicted)
	{
		ITEM_AT(queue->itemsAmount).address = feedback.evictedItem.address;
	}
	feedback.added = true;
	feedback.addedItem = ITEM_AT(queue->itemsAmount);
	queue->itemsAmount++;
	priority_queue_bubble_up(queue, queue->itemsAmount - 1);
	return feedback;
}

bool
priority_queue_pop_at(PriorityQueue *queue, int i, void **returnItemAddress)
{
	if (queue->itemsAmount == 0)
	{
		return false;
	}
	Item item = ITEM_AT(i);
	priority_queue_swap(queue, i, queue->itemsAmount - 1);
	queue->itemsAmount--;
	priority_queue_trickle_down(queue, i, true); //enforce minmax heap property
	if (returnItemAddress != NULL)
	{
		*returnItemAddress = item.address;
	}
	return true;
}

void
priority_queue_rebuild(PriorityQueue *queue)
{
	for (int i = 0; i < queue->itemsAmount; i++)
	{
		priority_queue_bubble_up(queue, i);
	}
}
