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

#ifndef H_HASHTABLE
#define H_HASHTABLE

/////////////////
//  HashTable  //
/////////////////
//The hashtable HT[Term] -> Concept*

//References//
//----------//
#include <stdlib.h>
#include <stdbool.h>
#include "nars_stack.h"

//Data structure//
//--------------//
typedef bool (*Equal)(void *, void *);
typedef HASH_TYPE (*Hash)(void *);
typedef struct
{
	void *key;
	void *value;
	void *next;
} VMItem;

typedef struct
{
	VMItem **storageptrs;
	VMItem *storage;
	VMItem **HT; //the hash of the concept term is the index
	Stack VMStack; //"Virtual memory" stack
	int buckets;
	Equal equal;
	Hash hash;
} HashTable;

//Methods//
//-------//
//Get a concept from the hashtable via term
void *
hashtable_get(HashTable *hashtable, void *key);

//Add a concept to the hashtable using the concept term
void
hashtable_set(HashTable *hashtable, void *key, void *value);

//Delete a concept from hashtable (the concept's term is the key)
void
hashtable_delete(HashTable *hashtable, void *key);

//Initialize hashtable "virtual memory" stack and HT array
void
hashtable_init(HashTable *hashtable,
               VMItem *storage,
               VMItem **storageptrs,
               VMItem **HT,
               int buckets,
               int maxElements,
               Equal equal,
               Hash hash);

//Maximum chain length in hashtable
int
hashtable_maximum_chain_length(HashTable *hashtable);

#endif

