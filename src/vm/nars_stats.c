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

#include "nars_stats.h"
#include "lib_slog.h"

long Stats_countConceptsMatchedTotal = 0;
long Stats_countConceptsMatchedMax = 0;

void
statsPrint(long currentTime)
{
	double Stats_averageBeliefEventPriority = 0.0;
	for (int i = 0; i < cycling_belief_events.itemsAmount; i++)
	{
		Stats_averageBeliefEventPriority += cycling_belief_events.items[i].priority;
	}
	Stats_averageBeliefEventPriority /= (double) CYCLING_BELIEF_EVENTS_MAX;
	double Stats_averageGoalEventPriority = 0.0;
	for (int i = 0; i < cycling_goal_events.itemsAmount; i++)
	{
		Stats_averageGoalEventPriority += cycling_goal_events.items[i].priority;
	}
	Stats_averageGoalEventPriority /= (double) CYCLING_GOAL_EVENTS_MAX;
	double Stats_averageConceptPriority = 0.0;
	for (int i = 0; i < concepts.itemsAmount; i++)
	{
		Concept *c = concepts.items[i].address;
		Stats_averageConceptPriority += c->priority;
	}
	Stats_averageConceptPriority /= (double) CONCEPTS_MAX;
	double Stats_averageConceptUsefulness = 0.0;
	for (int i = 0; i < concepts.itemsAmount; i++)
	{
		Stats_averageConceptUsefulness += concepts.items[i].priority;
	}
	Stats_averageConceptUsefulness /= (double) CONCEPTS_MAX;
	slog_info("BumbleStack Statistics:");
	printf("\tConcepts matched total:\t\t\t\t\t\t%ld\n", Stats_countConceptsMatchedTotal);
	printf("\tConcepts matched max:\t\t\t\t\t\t%ld\n", Stats_countConceptsMatchedMax);
	long countConceptsMatchedAverage = Stats_countConceptsMatchedTotal / currentTime;
	printf("\tConcepts matched average:\t\t\t\t\t%ld\n", countConceptsMatchedAverage);
	printf("\tCurrent internal system time:\t\t\t\t%ld\n", currentTime);
	printf("\tTotal concepts:\t\t\t\t\t\t\t\t%d\n", concepts.itemsAmount);
	printf("\tCurrent average concept priority:\t\t\t%f\n", Stats_averageConceptPriority);
	printf("\tCurrent average concept usefulness:\t\t\t%f\n", Stats_averageConceptUsefulness);
	printf("\tCurrent belief events count:\t\t\t\t%d\n", cycling_belief_events.itemsAmount);
	printf("\tCurrent goal events count:\t\t\t\t\t%d\n", cycling_goal_events.itemsAmount);
	printf("\tCurrent average belief event priority:\t\t%f\n", Stats_averageBeliefEventPriority);
	printf("\tCurrent average goal event priority:\t\t%f\n", Stats_averageGoalEventPriority);
	printf("\tMaximum chain length in concept hashtable:\t%d\n", HashTable_MaximumChainLength(&HTconcepts));
	printf("\tMaximum chain length in atoms hashtable: \t%d\n", HashTable_MaximumChainLength(&HTatoms));
	fflush(stdout);
}
