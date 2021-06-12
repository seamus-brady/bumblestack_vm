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

#include "nars_inverted_atom_index.h"
#include "lib_slog.h"

ConceptChainElement *g_conceptChainElementStoragePointers[UNIFICATION_DEPTH * CONCEPTS_MAX];
ConceptChainElement g_conceptChainElementStorage[UNIFICATION_DEPTH * CONCEPTS_MAX];
Stack g_conceptChainElementStack;
ConceptChainElement *g_invertedAtomIndex[ATOMS_MAX];

void
inverted_atom_index_init()
{
	for (int i = 0; i < ATOMS_MAX; i++)
	{
		g_invertedAtomIndex[i] = NULL;
	}
	stack_init(&g_conceptChainElementStack, (void **) g_conceptChainElementStoragePointers,
	           UNIFICATION_DEPTH * CONCEPTS_MAX);
	for (int i = 0; i < UNIFICATION_DEPTH * CONCEPTS_MAX; i++)
	{
		g_conceptChainElementStorage[i] = (ConceptChainElement) {0};
		g_conceptChainElementStoragePointers[i] = NULL;
		stack_push(&g_conceptChainElementStack, &g_conceptChainElementStorage[i]);
	}
}

void
inverted_atom_index_add_concept(Term term, Concept *c)
{
	for (int i = 0; i < UNIFICATION_DEPTH; i++)
	{
		Atom atom = term.atoms[i];
		if (narsese_is_simple_atom(atom))
		{
			ConceptChainElement *elem = g_invertedAtomIndex[atom];
			if (elem == NULL)
			{
				ConceptChainElement *newElem = stack_pop(&g_conceptChainElementStack); //new item
				newElem->c = c;
				g_invertedAtomIndex[atom] = newElem;
			}
			else
			{
				//search for vm:
				ConceptChainElement *previous = NULL;
				while (elem != NULL)
				{
					if (elem->c == c)
					{
						goto NEXT_ATOM;
					}
					previous = elem;
					elem = elem->next;
				}
				//ok, we can add it as previous->next
				ConceptChainElement *newElem = stack_pop(&g_conceptChainElementStack); //new item
				newElem->c = c;
				previous->next = newElem;
			}
		}
		NEXT_ATOM:;
	}
}

void
inverted_atom_index_remove_concept(Term term, Concept *c)
{
	for (int i = 0; i < UNIFICATION_DEPTH; i++)
	{
		Atom atom = term.atoms[i];
		if (narsese_is_simple_atom(atom))
		{
			ConceptChainElement *previous = NULL;
			ConceptChainElement *elem = g_invertedAtomIndex[atom];
			while (elem != NULL)
			{
				if (elem->c == c) //we found vm in the chain, remove it
				{
					if (previous == NULL) //item was the initial chain element, let the next element be the initial now
					{
						g_invertedAtomIndex[atom] = elem->next;
					}
					else //item was within the chain, relink the previous to the next of elem
					{
						previous->next = elem->next;
					}
					//push elem back to the stack, it's "freed"
					ASSERT(elem->c != NULL, "A null concept was in inverted atom index!");
					elem->c = NULL;
					elem->next = NULL;
					stack_push(&g_conceptChainElementStack, elem);
					goto NEXT_ATOM;
				}
				previous = elem;
				elem = elem->next;
			}
		}
		NEXT_ATOM:;
	}
}

void
inverted_atom_index_print()
{
	slog_info("Printing inverted atom table content:");
	for (int i = 0; i < ATOMS_MAX; i++)
	{
		Atom atom = i; //the atom is directly the value (from 0 to ATOMS_MAX)
		if (narsese_is_simple_atom(atom))
		{
			ConceptChainElement *elem = g_invertedAtomIndex[atom];
			while (elem != NULL)
			{
				Concept *c = elem->c;
				ASSERT(c != NULL, "A null concept was in inverted atom index!");
				narsese_print_atom(atom);
				fputs(" -> ", stdout);
				narsese_print_term(&c->term);
				puts("");
				elem = elem->next;
			}
		}
	}
	slog_info("Finished printing inverted atom table.");
}

ConceptChainElement *
inverted_atom_index_get_concept_chain(Atom atom)
{
	ConceptChainElement *ret = NULL;
	if (atom != 0)
	{
		ret = g_invertedAtomIndex[atom];
	}
	return ret;
}
