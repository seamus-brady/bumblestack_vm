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

#include "nars_event.h"

long base = 1;

Event
Event_InputEvent(Term term, char type, Truth truth, long currentTime)
{
	return (Event) {.term = term,
		.type = type,
		.truth = truth,
		.stamp = (Stamp) {.evidentialBase = {base++}},
		.occurrenceTime = currentTime,
		.creationTime = currentTime};
}

void
Event_INIT()
{
	base = 1;
}

bool
Event_Equal(Event *event, Event *existing)
{
	return Truth_Equal(&event->truth, &existing->truth) && Term_Equal(&event->term, &existing->term);
}
