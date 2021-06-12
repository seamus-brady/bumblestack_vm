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

#include "nars_truth.h"

double TRUTH_EVIDENTAL_HORIZON = TRUTH_EVIDENTAL_HORIZON_INITIAL;
double TRUTH_PROJECTION_DECAY = TRUTH_PROJECTION_DECAY_INITIAL;
#define TruthValues(v1, v2, f1, c1, f2, c2) double f1 = v1.frequency; double f2 = v2.frequency; double c1 = v1.confidence; double c2 = v2.confidence;

double
truth_w2c(double w)
{
	return w / (w + TRUTH_EVIDENTAL_HORIZON);
}

double
truth_c2w(double c)
{
	return TRUTH_EVIDENTAL_HORIZON * c / (1 - c);
}

double
truth_expectation(Truth v)
{
	return (v.confidence * (v.frequency - 0.5) + 0.5);
}

Truth
truth_revision(Truth v1, Truth v2)
{
	TruthValues(v1, v2, f1, c1, f2, c2);
	double w1 = truth_c2w(c1);
	double w2 = truth_c2w(c2);
	double w = w1 + w2;
	return (Truth) {.frequency = MIN(1.0, (w1 * f1 + w2 * f2) / w),
		.confidence = MIN(MAX_CONFIDENCE, MAX(MAX(truth_w2c(w), c1), c2))};
}

Truth
truth_deduction(Truth v1, Truth v2)
{
	TruthValues(v1, v2, f1, c1, f2, c2);
	double f = f1 * f2;
	return (Truth) {.frequency = f, .confidence = c1 * c2 * f};
}

Truth
truth_abduction(Truth v1, Truth v2)
{
	TruthValues(v1, v2, f1, c1, f2, c2);
	return (Truth) {.frequency = f2, .confidence = truth_w2c(f1 * c1 * c2)};
}

Truth
truth_induction(Truth v1, Truth v2)
{
	return truth_abduction(v2, v1);
}

Truth
truth_intersection(Truth v1, Truth v2)
{
	TruthValues(v1, v2, f1, c1, f2, c2);
	return (Truth) {.frequency = f1 * f2, .confidence = c1 * c2};
}

Truth
truth_eternalise(Truth v)
{
	return (Truth) {.frequency = v.frequency, .confidence = truth_w2c(v.confidence)};
}

Truth
truth_projection(Truth v, long originalTime, long targetTime)
{
	double difference = labs(targetTime - originalTime);
	return originalTime == OCCURRENCE_ETERNAL ?
	       v : (Truth) {.frequency = v.frequency, .confidence = v.confidence * pow(TRUTH_PROJECTION_DECAY, difference)};
}

void
truth_print(Truth *truth)
{
	printf(" truth=(frequency=%f, confidence=%f) \n", truth->frequency, truth->confidence);
}

void
truth_print2(Truth *truth)
{
	printf("{%f %f} \n", truth->frequency, truth->confidence);
}

//not part of MSC:

Truth
truth_exemplification(Truth v1, Truth v2)
{
	TruthValues(v1, v2, f1, c1, f2, c2);
	return (Truth) {.frequency = 1.0, .confidence = truth_w2c(f1 * f2 * c1 * c2)};
}

static inline double
or(double a, double b)
{
	return 1.0 - (1.0 - a) * (1.0 - b);
}

Truth
truth_comparison(Truth v1, Truth v2)
{
	TruthValues(v1, v2, f1, c1, f2, c2);
	double f0 = or(f1, f2);
	return (Truth) {.frequency = (f0 == 0.0) ? 0.0 : ((f1 * f2) / f0), .confidence = truth_w2c(f0 * c1 * c2)};
}

Truth
truth_analogy(Truth v1, Truth v2)
{
	TruthValues(v1, v2, f1, c1, f2, c2);
	return (Truth) {.frequency = f1 * f2, .confidence = c1 * c2 * f2};
}

Truth
truth_resemblance(Truth v1, Truth v2)
{
	TruthValues(v1, v2, f1, c1, f2, c2);
	return (Truth) {.frequency = f1 * f2, .confidence = c1 * c2 * or(f1, f2)};
}

Truth
truth_union(Truth v1, Truth v2)
{
	TruthValues(v1, v2, f1, c1, f2, c2);
	return (Truth) {.frequency = or(f1, f2), .confidence = c1 * c2};
}

Truth
truth_difference(Truth v1, Truth v2)
{
	TruthValues(v1, v2, f1, c1, f2, c2);
	return (Truth) {.frequency = f1 * (1.0 - f2), .confidence = c1 * c2};
}

Truth
truth_conversion(Truth v1, Truth v2)
{
	return (Truth) {.frequency = 1.0, .confidence = truth_w2c(v1.frequency * v1.confidence)};
}

Truth
truth_negation(Truth v1, Truth v2)
{
	TruthValues(v1, v2, f1, c1, f2, c2);
	return (Truth) {.frequency = 1.0 - f1, .confidence = c1};
}

Truth
truth_structural_deduction(Truth v1, Truth v2)
{
	return truth_deduction(v1, STRUCTURAL_TRUTH);
}

Truth
truth_structural_deduction_negated(Truth v1, Truth v2)
{
	return truth_negation(truth_deduction(v1, STRUCTURAL_TRUTH), v2);
}

Truth
truth_structural_abduction(Truth v1, Truth v2)
{
	return truth_abduction(v1, STRUCTURAL_TRUTH);
}

bool
truth_equal(Truth *v1, Truth *v2)
{
	return v1->confidence == v2->confidence && v1->frequency == v2->frequency;
}

Truth
truth_decompose_pnn(Truth v1, Truth v2)
{
	TruthValues(v1, v2, f1, c1, f2, c2);
	double fn = f1 * (1.0 - f2);
	return (Truth) {.frequency = 1.0 - fn, .confidence = fn * c1 * c2};
}

Truth
truth_decompose_npp(Truth v1, Truth v2)
{
	TruthValues(v1, v2, f1, c1, f2, c2);
	double f = (1.0 - f1) * f2;
	return (Truth) {.frequency = f, .confidence = f * c1 * c2};
}

Truth
truth_decompose_pnp(Truth v1, Truth v2)
{
	TruthValues(v1, v2, f1, c1, f2, c2);
	double f = f1 * (1.0 - f2);
	return (Truth) {.frequency = f, .confidence = f * c1 * c2};
}

Truth
truth_decompose_ppp(Truth v1, Truth v2)
{
	return truth_decompose_npp(truth_negation(v1, v2), v2);
}

Truth
truth_decompose_nnn(Truth v1, Truth v2)
{
	TruthValues(v1, v2, f1, c1, f2, c2);
	double fn = (1.0 - f1) * (1.0 - f2);
	return (Truth) {.frequency = 1.0 - fn, .confidence = fn * c1 * c2};
}
