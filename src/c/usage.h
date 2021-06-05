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

#ifndef H_USAGE
#define H_USAGE

////////////////////////////////
//  concept usefulness value  //
////////////////////////////////

//References//
//----------//
#include <stdio.h>
#include <stdbool.h>
#include "config.h"

//Data structure//
//--------------//
typedef struct {
    //use_count, how often it was used in total
    long useCount;
    //age, how many cycles ago it was last used
    long lastUsed;
} Usage;

//Methods//
//-------//
//how useful it is in respect to the current moment
double Usage_usefulness(Usage usage, long currentTime);
//use the item
Usage Usage_use(Usage usage, long currentTime, bool eternalInput);
//print it
void Usage_Print(Usage *usage);

#endif
