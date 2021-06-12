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

#ifndef H_TRUTH
#define H_TRUTH

////////////////////////////////////////////
//  NAL truth value and truth functions   //
////////////////////////////////////////////

//References//
//----------//
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "nars_globals.h"
#include "nars_config.h"

//Data structure//
//--------------//
typedef struct
{
	//Frequency
	double frequency;
	//Confidence
	double confidence;
} Truth;

//Parameters//
//----------//
extern double TRUTH_EVIDENTAL_HORIZON;

extern double TRUTH_PROJECTION_DECAY;

#define OCCURRENCE_ETERNAL -1

#define STRUCTURAL_TRUTH (Truth) { .frequency = 1.0, .confidence = RELIANCE }

//Methods//
//-------//
double
truth_w2c(double w);

double
truth_c2w(double c);

double
truth_expectation(Truth v);

Truth
truth_revision(Truth v1, Truth v2);

Truth
truth_deduction(Truth v1, Truth v2);

Truth
truth_induction(Truth v1, Truth v2);

Truth
truth_intersection(Truth v1, Truth v2);

Truth
truth_eternalise(Truth v);

Truth
truth_projection(Truth v, long originalTime, long targetTime);

void
truth_print(Truth *truth);

void
truth_print2(Truth *truth);

//not part of sensorimotor inference:
Truth
truth_abduction(Truth v1, Truth v2);

Truth
truth_exemplification(Truth v1, Truth v2);

Truth
truth_comparison(Truth v1, Truth v2);

Truth
truth_analogy(Truth v1, Truth v2);

Truth
truth_resemblance(Truth v1, Truth v2);

Truth
truth_structural_deduction(Truth v1, Truth v2);

Truth
truth_structural_deduction_negated(Truth v1, Truth v2);

Truth
truth_structural_abduction(Truth v1, Truth v2);

Truth
truth_union(Truth v1, Truth v2);

Truth
truth_difference(Truth v1, Truth v2);

Truth
truth_conversion(Truth v1, Truth v2);

Truth
truth_negation(Truth v1, Truth v2);

Truth
truth_decompose_pnn(Truth v1, Truth v2);

Truth
truth_decompose_npp(Truth v1, Truth v2);

Truth
truth_decompose_pnp(Truth v1, Truth v2);

Truth
truth_decompose_ppp(Truth v1, Truth v2);

Truth
truth_decompose_nnn(Truth v1, Truth v2);

bool
truth_equal(Truth *v1, Truth *v2);

#endif
