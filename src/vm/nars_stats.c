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

long g_statsCountConceptsMatchedTotal = 0;
long g_statsCountConceptsMatchedMax = 0;

void
stats_print(long currentTime)
{
	double Stats_averageBeliefEventPriority = 0.0;
	for (int i = 0; i < g_cyclingBeliefEvents.itemsAmount; i++)
	{
		Stats_averageBeliefEventPriority += g_cyclingBeliefEvents.items[i].priority;
	}
	Stats_averageBeliefEventPriority /= (double) CYCLING_BELIEF_EVENTS_MAX;
	double Stats_averageGoalEventPriority = 0.0;
	for (int i = 0; i < g_cyclingGoalEvents.itemsAmount; i++)
	{
		Stats_averageGoalEventPriority += g_cyclingGoalEvents.items[i].priority;
	}
	Stats_averageGoalEventPriority /= (double) CYCLING_GOAL_EVENTS_MAX;
	double Stats_averageConceptPriority = 0.0;
	for (int i = 0; i < g_concepts.itemsAmount; i++)
	{
		Concept *c = g_concepts.items[i].address;
		Stats_averageConceptPriority += c->priority;
	}
	Stats_averageConceptPriority /= (double) CONCEPTS_MAX;
	double Stats_averageConceptUsefulness = 0.0;
	for (int i = 0; i < g_concepts.itemsAmount; i++)
	{
		Stats_averageConceptUsefulness += g_concepts.items[i].priority;
	}
	Stats_averageConceptUsefulness /= (double) CONCEPTS_MAX;
	slog_info("BumbleStack Statistics:");
	printf("\tConcepts matched total:\t\t\t\t\t\t%ld\n", g_statsCountConceptsMatchedTotal);
	printf("\tConcepts matched max:\t\t\t\t\t\t%ld\n", g_statsCountConceptsMatchedMax);
	long countConceptsMatchedAverage = g_statsCountConceptsMatchedTotal / currentTime;
	printf("\tConcepts matched average:\t\t\t\t\t%ld\n", countConceptsMatchedAverage);
	printf("\tCurrent internal system time:\t\t\t\t%ld\n", currentTime);
	printf("\tTotal g_concepts:\t\t\t\t\t\t\t\t%d\n", g_concepts.itemsAmount);
	printf("\tCurrent average concept priority:\t\t\t%f\n", Stats_averageConceptPriority);
	printf("\tCurrent average concept usefulness:\t\t\t%f\n", Stats_averageConceptUsefulness);
	printf("\tCurrent belief events count:\t\t\t\t%d\n", g_cyclingBeliefEvents.itemsAmount);
	printf("\tCurrent goal events count:\t\t\t\t\t%d\n", g_cyclingGoalEvents.itemsAmount);
	printf("\tCurrent average belief event priority:\t\t%f\n", Stats_averageBeliefEventPriority);
	printf("\tCurrent average goal event priority:\t\t%f\n", Stats_averageGoalEventPriority);
	printf("\tMaximum chain length in concept hashtable:\t%d\n", hashtable_maximum_chain_length(&g_hashtableConceptsStruct));
	printf("\tMaximum chain length in atoms hashtable: \t%d\n", hashtable_maximum_chain_length(&g_hashtableAtomsStruct));
	fflush(stdout);
}
