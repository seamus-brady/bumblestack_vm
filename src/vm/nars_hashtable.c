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

#include "nars_hashtable.h"

void *
hashtable_get(HashTable *hashtable, void *key)
{
	HASH_TYPE keyhash = hashtable->hash(key) % hashtable->buckets;
	VMItem *item = hashtable->HT[keyhash];
	for (; item != NULL; item = item->next)
	{
		if (hashtable->equal(item->key, key))
		{
			return item->value;
		}
	}
	return NULL;
}

void
hashtable_set(HashTable *hashtable, void *key, void *value)
{
	HASH_TYPE keyhash = hashtable->hash(key) % hashtable->buckets;
	//Check if item already exists in hashtable, if yes return
	VMItem *item = hashtable->HT[keyhash];
	bool empty = item == NULL;
	if (!empty)
	{
		for (; item->next != NULL; item = item->next)
		{
			if (hashtable->equal(item->key, key))
			{
				return;
			}
		}
	}
	//Retrieve recycled VMItem from the stack and set its value to vm
	VMItem *popped = stack_pop(&hashtable->VMStack);
	popped->value = value;
	popped->key = key;
	popped->next = NULL;
	//Case1: HT ITEM_AT hash was empty so add recycled item ITEM_AT HT[keyhash]
	if (empty)
	{
		hashtable->HT[keyhash] = popped;
	}
		//Case2: HT ITEM_AT hash not empty so add recycled item ITEM_AT end of the chain of HT[keyhash]
	else
	{
		ASSERT(item != NULL, "VMItem should not be null!");
		item->next = popped;
	}
}

void
hashtable_delete(HashTable *hashtable, void *key)
{
	HASH_TYPE keyhash = hashtable->hash(key) % hashtable->buckets;
	VMItem *item = hashtable->HT[keyhash];
	VMItem *previous = NULL;
	//If there is only one item set HT[keyhash] to NULL and push back the VMItem to stack for recycling
	if (item->next == NULL)
	{
		hashtable->HT[keyhash] = NULL;
		stack_push(&hashtable->VMStack, item);
		return;
	}
	//If there is more than 1 item, we have to remove the item from chain, relinking previous to next
	for (; item != NULL; previous = item, item = item->next)
	{
		//item found?
		if (hashtable->equal(item->key, key))
		{
			//remove item and return
			if (previous == NULL)
			{
				hashtable->HT[keyhash] = item->next;
			}
			else
			{
				previous->next = item->next;
			}
			stack_push(&hashtable->VMStack, item);
			return;
		}
	}
	ASSERT(false, "HashTable deletion failed, item was not found!");
}

void
hashtable_init(HashTable *hashtable, VMItem *storage, VMItem **storageptrs, VMItem **HT, int buckets, int maxElements,
               Equal equal, Hash hash)
{
	hashtable->storage = storage;
	hashtable->storageptrs = storageptrs;
	hashtable->HT = HT;
	hashtable->VMStack = (Stack) {0};
	stack_init(&hashtable->VMStack, (void **) hashtable->storageptrs, maxElements);
	hashtable->equal = equal;
	hashtable->hash = hash;
	hashtable->buckets = buckets;
	for (int i = 0; i < buckets; i++)
	{
		hashtable->HT[i] = NULL;
	}
	for (int i = 0; i < maxElements; i++)
	{
		hashtable->storage[i] = (VMItem) {0};
		hashtable->storageptrs[i] = NULL;
		stack_push(&hashtable->VMStack, &hashtable->storage[i]);
	}
}

int
hashtable_maximum_chain_length(HashTable *hashtable)
{
	int maxlen = 0;
	for (int i = 0; i < hashtable->buckets; i++)
	{
		VMItem *item = hashtable->HT[i];
		int cnt = 0;
		for (; item != NULL; item = item->next, cnt++);
		maxlen = MAX(maxlen, cnt);
	}
	return maxlen;
}
