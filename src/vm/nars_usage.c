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

#include "nars_usage.h"

double
Usage_usefulness(Usage usage, long currentTime)
{
	double recency = currentTime - usage.lastUsed;
	double usefulnessToNormalize = ((double) usage.useCount) / (recency + 1.0);
	return usefulnessToNormalize / (usefulnessToNormalize + 1.0);
}

Usage
Usage_use(Usage usage, long currentTime, bool eternalInput)
{
	return (Usage) {.useCount = usage.useCount + (eternalInput ? ETERNAL_INPUT_USAGE_BOOST : 1),
		.lastUsed = currentTime};
}

void
Usage_Print(Usage *usage)
{
	printf("Usage: useCount=%ld lastUsed=%ld\n", usage->useCount, usage->lastUsed);
}
