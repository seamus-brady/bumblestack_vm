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

#ifndef H_CONFIG
#define H_CONFIG

/*-------------------------*/
/* Anticipation parameters */
/*-------------------------*/
//Truth expectation needed for anticipation
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#define ANTICIPATION_THRESHOLD_INITIAL 0.501
//Confidence of anticipation failures
#define ANTICIPATION_CONFIDENCE_INITIAL 0.005

/*---------------------*/
/* Decision parameters */
/*---------------------*/
//Truth expectation to move on to next component goal in sequence
#define CONDITION_THRESHOLD_INITIAL 0.501
//Desire expectation needed for executions
#define DECISION_THRESHOLD_INITIAL 0.501
//Motor babbling chance
#define MOTOR_BABBLING_CHANCE_INITIAL 0.2
//Decisions above the following threshold will suppress babbling actions
#define MOTOR_BABBLING_SUPPRESSION_THRESHOLD 0.55

/*----------------------*/
/* Attention parameters */
/*----------------------*/
//Event selections per cycle for inference
#define BELIEF_EVENT_SELECTIONS 1
//Goal event selections per cycle for inference
#define GOAL_EVENT_SELECTIONS 1
//Event priority decay of events per cycle
#define EVENT_DURABILITY 0.9999
//Additional event priority decay of an event which was used
#define EVENT_DURABILITY_ON_USAGE 0.0
//Concept priority decay of events per cycle
#define CONCEPT_DURABILITY 0.9
//Minimum confidence to accept events
#define MIN_CONFIDENCE 0.01
//Minimum priority to accept events
#define MIN_PRIORITY 0
//Occurrence time distance in which case event belief is preferred over eternal
#define EVENT_BELIEF_DISTANCE 20
//Amount of belief g_concepts to select to be matched to the selected event
#define BELIEF_CONCEPT_MATCH_TARGET 80
//Adaptation speed of the concept priority threshold to meet the match target
#define CONCEPT_THRESHOLD_ADAPTATION 0.000001
//Usage boost for input
#define ETERNAL_INPUT_USAGE_BOOST 1000000
//Unification depth, 2^(n+1)-1, n=2 levels lead to value 7
#define UNIFICATION_DEPTH 7

/*------------------*/
/* Space parameters */
/*------------------*/
//Maximum amount of g_concepts
#define CONCEPTS_MAX 16384
//Amount of buckets for concept hashmap
#define CONCEPTS_HASHTABLE_BUCKETS CONCEPTS_MAX
//Maximum amount of belief events attention buffer holds
#define CYCLING_BELIEF_EVENTS_MAX 40
//Maximum amount of goal events attention buffer holds
#define CYCLING_GOAL_EVENTS_MAX 40
//Maximum amount of g_operations which can be registered
#define OPERATIONS_MAX 10
//Maximum size of the stamp in terms of evidental g_base id's
#define STAMP_SIZE 10
//Maximum event FIFO size
#define FIFO_SIZE 20
//Maximum Implication table size
#define TABLE_SIZE 20
//Maximum length of sequences
#define MAX_SEQUENCE_LEN 3
//Maximum compound term size
#define COMPOUND_TERM_SIZE_MAX 64
//Max. amount of atomic terms, must be <= 2^(sizeof(Atom)*8)
#define ATOMS_MAX 65536
//Amount of buckets for atoms hashmap
#define ATOMS_HASHTABLE_BUCKETS ATOMS_MAX
//The type of an atom
#define Atom unsigned short
//Maximum size of atomic terms in terms of characters
#define ATOMIC_TERM_LEN_MAX 32
//Maximum size of Narsese input in terms of characters
#define NARSESE_LEN_MAX 256
//Maximum size of script input in terms of characters
#define SCRIPT_LEN_MAX 256
// max number of lines in a provided script
#define MAX_SCRIPT_FILE_LINES 600

/*------------------*/
/* Truth parameters */
/*------------------*/
//Default frequency for input events
#define NAR_DEFAULT_FREQUENCY  1.0
//Default confidence for input events
#define NAR_DEFAULT_CONFIDENCE 0.9
//Default confidence for analytical premise
#define RELIANCE 0.9
//NAL evidental horizon
#define TRUTH_EVIDENTAL_HORIZON_INITIAL 1.0
//Time distance based projection decay of event truth
#define TRUTH_PROJECTION_DECAY_INITIAL 0.8
//Maximum value for confidence
#define MAX_CONFIDENCE 0.99

/*------------------*/
/* Runtime parameters */
/*------------------*/

// random seed
#define SEED 42

//Whether debug mode should be on
#define DEBUG_MODE false

//Whether asserts cause exits
#define EXIT_ON_ASSERT_FAIL true

//Whether control information should be printed - leave as debug mode for now
#define PRINT_CONTROL_INFO DEBUG_MODE

//Priority threshold for printing derivations  - leave as debug mode for now
#define PRINT_DERIVATIONS_PRIORITY_THRESHOLD 0.0



#endif
