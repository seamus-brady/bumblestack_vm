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

#include "nal.h"

int ruleID = 0;

static void NAL_GeneratePremisesUnifier(int i, Atom atom, int premiseIndex) {
    if (atom) {
        //upper case atoms are treated as variables in the meta rule language
        if (Narsese_atomNames[atom - 1][0] >= 'A' && Narsese_atomNames[atom - 1][0] <= 'Z') {
            //unification failure by inequal value assignment (value at position i versus previously assigned one), and variable binding
            printf("subtree = Term_ExtractSubterm(&term%d, %d);\n", premiseIndex, i);
            printf("if((substitutions[%d].atoms[0]!=0 && !Term_Equal(&substitutions[%d], &subtree)) || Narsese_copulaEquals(subtree.atoms[0], '@')){ goto RULE_%d; }\n",
                   atom, atom, ruleID);
            printf("substitutions[%d] = subtree;\n", atom);
        } else {
            //structural constraint given by copulas at position i
            printf("if(term%d.atoms[%d] != %d){ goto RULE_%d; }\n", premiseIndex, i, atom, ruleID);
        }
    }
}

static void NAL_GenerateConclusionSubstitution(int i, Atom atom) {
    if (atom) {
        if (Narsese_atomNames[atom - 1][0] >= 'A' && Narsese_atomNames[atom - 1][0] <= 'Z') {
            //conclusion term gets variables substituted
            printf("if(!Term_OverrideSubterm(&conclusion,%d,&substitutions[%d])){ goto RULE_%d; }\n", i, atom, ruleID);
        } else {
            //conclusion term inherits structure from meta rule, namely the copula
            printf("conclusion.atoms[%d] = %d;\n", i, atom);
        }
    }
}

static void NAL_GenerateConclusionTerm(char *premise1, char *premise2, char *conclusion, bool doublePremise) {
    Term term1 = Narsese_Term(premise1);
    Term term2 = doublePremise ? Narsese_Term(premise2) : (Term) {0};
    Term conclusion_term = Narsese_Term(conclusion);
    printf("RULE_%d:\n{\n", ruleID++);
    //skip double/single premise rule if single/double premise
    if (doublePremise) { printf("if(!doublePremise) { goto RULE_%d; }\n", ruleID); }
    if (!doublePremise) { printf("if(doublePremise) { goto RULE_%d; }\n", ruleID); }
    puts("Term substitutions[27+NUM_ELEMENTS(Narsese_RuleTableVars)] = {0}; Term subtree = {0};"); //27 because of 9 indep, 9 dep, 9 query vars
    for (int i = 0; i < COMPOUND_TERM_SIZE_MAX; i++) {
        NAL_GeneratePremisesUnifier(i, term1.atoms[i], 1);
    }
    if (doublePremise) {
        for (int i = 0; i < COMPOUND_TERM_SIZE_MAX; i++) {
            NAL_GeneratePremisesUnifier(i, term2.atoms[i], 2);
        }
    }
    puts("Term conclusion = {0};");
    for (int i = 0; i < COMPOUND_TERM_SIZE_MAX; i++) {
        NAL_GenerateConclusionSubstitution(i, conclusion_term.atoms[i]);
    }
}

static void NAL_GenerateRule(char *premise1, char *premise2, char *conclusion, char *truthFunction, bool doublePremise,
                             bool switchTruthArgs) {
    NAL_GenerateConclusionTerm(premise1, premise2, conclusion, doublePremise);
    if (switchTruthArgs) {
        printf("Truth conclusionTruth = %s(truth2,truth1);\n", truthFunction);
    } else {
        printf("Truth conclusionTruth = %s(truth1,truth2);\n", truthFunction);
    }
    puts("NAL_DerivedEvent(RuleTableReduce(conclusion, false), conclusionOccurrence, conclusionTruth, conclusionStamp, currentTime, parentPriority, conceptPriority, occurrenceTimeOffset, validation_concept, validation_cid);}\n");
}

static void NAL_GenerateReduction(char *premise1, char *conclusion) {
    NAL_GenerateConclusionTerm(premise1, NULL, conclusion, false);
    puts("IS_SYSTEM_IN_DEBUG_MODE( fputs(\"Reduced: \", stdout); Narsese_PrintTerm(&term1); fputs(\" -> \", stdout); Narsese_PrintTerm(&conclusion); puts(\"\"); ) \nreturn conclusion;\n}");
}

void NAL_GenerateRuleTable() {
    puts("#include \"ruletable.h\"");
    puts("void RuleTableApply(Term term1, Term term2, Truth truth1, Truth truth2, long conclusionOccurrence, double occurrenceTimeOffset, Stamp conclusionStamp, long currentTime, double parentPriority, double conceptPriority, bool doublePremise, Concept *validation_concept, long validation_cid)\n{\ngoto RULE_0;");
#define H_NAL_RULES

#include "nal.h"

#undef H_NAL_RULES
    printf("RULE_%d:;\n}\n", ruleID);
    printf("Term RuleTableReduce(Term term1, bool doublePremise)\n{\ngoto RULE_%d;\n", ruleID);
#define H_NAL_REDUCTIONS

#include "nal.h"

#undef H_NAL_REDUCTIONS
    printf("RULE_%d:;\nreturn term1;\n}\n\n", ruleID);
}

static int atomsCounter = 1; //allows to avoid memset
static int atomsAppeared[ATOMS_MAX] = {0};

static bool NAL_AtomAppearsTwice(Term *conclusionTerm) {
    if (Narsese_copulaEquals(conclusionTerm->atoms[0], ':') ||
        Narsese_copulaEquals(conclusionTerm->atoms[0], '=')) //similarity or inheritance
    {
        atomsCounter++;
        for (int i = 0; i < COMPOUND_TERM_SIZE_MAX; i++) {
            Atom atom = conclusionTerm->atoms[i];
            if (atomsAppeared[conclusionTerm->atoms[i]] == atomsCounter) //atom already appeared
            {
                return true;
            }
            if (Narsese_IsNonCopulaAtom(atom)) {
                atomsAppeared[atom] = atomsCounter;
            }
        }
    }
    return false;
}

void
NAL_DerivedEvent(Term conclusionTerm, long conclusionOccurrence, Truth conclusionTruth, Stamp stamp, long currentTime,
                 double parentPriority, double conceptPriority, double occurrenceTimeOffset,
                 Concept *validation_concept, long validation_cid) {
    Event e = {.term = conclusionTerm,
            .type = EVENT_TYPE_BELIEF,
            .truth = conclusionTruth,
            .stamp = stamp,
            .occurrenceTime = conclusionOccurrence,
            .creationTime = currentTime};
    if (validation_concept == NULL || validation_concept->id == validation_cid) {
        //concept recycling would invalidate the derivation (allows to lock only adding results to memory)
        if (!NAL_AtomAppearsTwice(&conclusionTerm)) {
            Memory_AddEvent(&e, currentTime, conceptPriority * parentPriority * Truth_Expectation(conclusionTruth),
                            occurrenceTimeOffset, false, true, false, false, false);
        }
    }
}
