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
#include "globals.h"
#include "config.h"

//Data structure//
//--------------//
typedef struct {
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
double Truth_w2c(double w);
double Truth_c2w(double c);
double Truth_Expectation(Truth v);
Truth Truth_Revision(Truth v1, Truth v2);
Truth Truth_Deduction(Truth v1, Truth v2);
Truth Truth_Induction(Truth v1, Truth v2);
Truth Truth_Intersection(Truth v1, Truth v2);
Truth Truth_Eternalize(Truth v);
Truth Truth_Projection(Truth v, long originalTime, long targetTime);
void Truth_Print(Truth *truth);
void Truth_Print2(Truth *truth);
//not part of sensorimotor inference:
Truth Truth_Abduction(Truth v1, Truth v2);
Truth Truth_Exemplification(Truth v1, Truth v2);
Truth Truth_Comparison(Truth v1, Truth v2);
Truth Truth_Analogy(Truth v1, Truth v2);
Truth Truth_Resemblance(Truth v1, Truth v2);
Truth Truth_StructuralDeduction(Truth v1, Truth v2);
Truth Truth_StructuralDeductionNegated(Truth v1, Truth v2);
Truth Truth_StructuralAbduction(Truth v1, Truth v2);
Truth Truth_Union(Truth v1, Truth v2);
Truth Truth_Difference(Truth v1, Truth v2);
Truth Truth_Conversion(Truth v1, Truth v2);
Truth Truth_Negation(Truth v1, Truth v2);
Truth Truth_DecomposePNN(Truth v1, Truth v2);
Truth Truth_DecomposeNPP(Truth v1, Truth v2);
Truth Truth_DecomposePNP(Truth v1, Truth v2);
Truth Truth_DecomposePPP(Truth v1, Truth v2);
Truth Truth_DecomposeNNN(Truth v1, Truth v2);
bool Truth_Equal(Truth *v1, Truth *v2);

#endif
