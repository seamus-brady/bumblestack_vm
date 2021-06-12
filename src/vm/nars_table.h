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

#ifndef H_TABLE
#define H_TABLE

///////////////
//   Table   //
///////////////
//A table of implications, ranked by truth expectation

//References//
//----------//
#include "nars_inference.h"
#include "nars_globals.h"
#include <string.h>
#include "nars_config.h"

//Data structure//
//--------------//
//A truth-expectation-ranked table for Implications, similar as pre- and post-condition table in OpenNARS,
//except that this table supports revision by itself (as in NAR implications don't form g_concepts).
typedef struct
{
	Implication array[TABLE_SIZE];
	int itemsAmount;
} Table;

//Methods//
//-------//
//Add implication to table
Implication *
Table_Add(Table *table, Implication *imp);
//Add element ITEM_AT index from table
void
Table_Remove(Table *table, int index);
//Add implication to table while allowing revision
Implication *
Table_AddAndRevise(Table *table, Implication *imp);

#endif
