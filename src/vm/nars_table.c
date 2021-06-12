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

#include "nars_table.h"

Implication *
Table_Add(Table *table, Implication *imp)
{
	ASSERT(imp->sourceConcept != NULL, "Attempted to add an implication without source concept!");
	double impTruthExp = Truth_Expectation(imp->truth);
	for (int i = 0; i < TABLE_SIZE; i++)
	{
		bool same_term = Term_Equal(&table->array[i].term, &imp->term);
		//either it's not yet full and we reached a new space,
		//or the term is different and the truth expectation is higher
		//or the term is the same and the confidence is higher
		if (i == table->itemsAmount || (!same_term && impTruthExp > Truth_Expectation(table->array[i].truth)) ||
			(same_term && imp->truth.confidence > table->array[i].truth.confidence))
		{
			//ok here it has to go, move down the rest, evicting the last element if we hit TABLE_SIZE-1.
			for (int j = MIN(table->itemsAmount, TABLE_SIZE - 1); j > i; j--)
			{
				table->array[j] = table->array[j - 1];
			}
			table->array[i] = *imp;
			table->itemsAmount = MIN(table->itemsAmount + 1, TABLE_SIZE);
			return &table->array[i];
		}
	}
	return NULL;
}

void
Table_Remove(Table *table, int index)
{
	//move up the rest beginning at index
	for (int j = index; j < table->itemsAmount; j++)
	{
		table->array[j] = j == table->itemsAmount - 1 ? (Implication) {0} : table->array[j + 1];
	}
	table->itemsAmount = MAX(0, table->itemsAmount - 1);
}

Implication *
Table_AddAndRevise(Table *table, Implication *imp)
{
	//1. find element with same Term
	int same_i = -1;
	for (int i = 0; i < table->itemsAmount; i++)
	{
		if (Term_Equal(&imp->term, &table->array[i].term))
		{
			same_i = i;
			break;
		}
	}
	//2. if there was one, revise with it or apply choice if overlap
	if (same_i != -1)
	{
		//revision adds the revised element, removing the old implication from the table
		Implication OldImp = table->array[same_i];
		ASSERT(OldImp.truth.frequency >= 0.0 && OldImp.truth.frequency <= 1.0, "(1) frequency out of bounds");
		ASSERT(OldImp.truth.confidence >= 0.0 && OldImp.truth.confidence <= 1.0, "(1) confidence out of bounds");
		ASSERT(imp->truth.frequency >= 0.0 && imp->truth.frequency <= 1.0, "(2) frequency out of bounds");
		ASSERT(imp->truth.confidence >= 0.0 && imp->truth.confidence <= 1.0, "(2) confidence out of bounds");
		Implication revised = inference_implication_revision(&OldImp, imp);
		ASSERT(revised.truth.frequency >= 0.0 && revised.truth.frequency <= 1.0, "(3) frequency out of bounds");
		ASSERT(revised.truth.confidence >= 0.0 && revised.truth.confidence <= 1.0, "(3) confidence out of bounds");
		revised.term = imp->term;
		Table_Remove(table, same_i);
		Implication *ret = Table_Add(table, &revised);
		ASSERT(ret != NULL, "Deletion and re-addition should have succeeded");
		return ret;
	}
	else
	{
		return Table_Add(table, imp);
	}
}
