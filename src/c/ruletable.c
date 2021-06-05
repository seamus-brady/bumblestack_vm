#include "ruletable.h"

void RuleTableApply(Term term1, Term term2, Truth truth1, Truth truth2, long conclusionOccurrence,
                    double occurrenceTimeOffset, Stamp conclusionStamp, long currentTime, double parentPriority,
                    double conceptPriority, bool doublePremise, Concept *validation_concept, long validation_cid) {
    goto RULE_0;
    RULE_0:
    {
        if (!doublePremise) { goto RULE_1; }
        Term substitutions[27 + NUM_ELEMENTS(Narsese_RuleTableVars)] = {0};
        Term subtree = {0};
        if (term1.atoms[0] != 43) { goto RULE_1; }
        subtree = Term_ExtractSubterm(&term1, 1);
        if ((substitutions[33].atoms[0] != 0 && !Term_Equal(&substitutions[33], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_1; }
        substitutions[33] = subtree;
        subtree = Term_ExtractSubterm(&term1, 2);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_1; }
        substitutions[31] = subtree;
        if (term2.atoms[0] != 43) { goto RULE_1; }
        subtree = Term_ExtractSubterm(&term2, 1);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_1; }
        substitutions[31] = subtree;
        subtree = Term_ExtractSubterm(&term2, 2);
        if ((substitutions[34].atoms[0] != 0 && !Term_Equal(&substitutions[34], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_1; }
        substitutions[34] = subtree;
        Term conclusion = {0};
        conclusion.atoms[0] = 43;
        if (!Term_OverrideSubterm(&conclusion, 1, &substitutions[33])) { goto RULE_1; }
        if (!Term_OverrideSubterm(&conclusion, 2, &substitutions[34])) { goto RULE_1; }
        Truth conclusionTruth = Truth_Deduction(truth1, truth2);
        NAL_DerivedEvent(RuleTableReduce(conclusion, false), conclusionOccurrence, conclusionTruth, conclusionStamp,
                         currentTime, parentPriority, conceptPriority, occurrenceTimeOffset, validation_concept,
                         validation_cid);
    }

    RULE_1:
    {
        if (!doublePremise) { goto RULE_2; }
        Term substitutions[27 + NUM_ELEMENTS(Narsese_RuleTableVars)] = {0};
        Term subtree = {0};
        if (term1.atoms[0] != 43) { goto RULE_2; }
        subtree = Term_ExtractSubterm(&term1, 1);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_2; }
        substitutions[31] = subtree;
        subtree = Term_ExtractSubterm(&term1, 2);
        if ((substitutions[34].atoms[0] != 0 && !Term_Equal(&substitutions[34], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_2; }
        substitutions[34] = subtree;
        if (term2.atoms[0] != 43) { goto RULE_2; }
        subtree = Term_ExtractSubterm(&term2, 1);
        if ((substitutions[33].atoms[0] != 0 && !Term_Equal(&substitutions[33], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_2; }
        substitutions[33] = subtree;
        subtree = Term_ExtractSubterm(&term2, 2);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_2; }
        substitutions[31] = subtree;
        Term conclusion = {0};
        conclusion.atoms[0] = 43;
        if (!Term_OverrideSubterm(&conclusion, 1, &substitutions[33])) { goto RULE_2; }
        if (!Term_OverrideSubterm(&conclusion, 2, &substitutions[34])) { goto RULE_2; }
        Truth conclusionTruth = Truth_Deduction(truth2, truth1);
        NAL_DerivedEvent(RuleTableReduce(conclusion, false), conclusionOccurrence, conclusionTruth, conclusionStamp,
                         currentTime, parentPriority, conceptPriority, occurrenceTimeOffset, validation_concept,
                         validation_cid);
    }

    RULE_2:
    {
        if (!doublePremise) { goto RULE_3; }
        Term substitutions[27 + NUM_ELEMENTS(Narsese_RuleTableVars)] = {0};
        Term subtree = {0};
        if (term1.atoms[0] != 43) { goto RULE_3; }
        subtree = Term_ExtractSubterm(&term1, 1);
        if ((substitutions[28].atoms[0] != 0 && !Term_Equal(&substitutions[28], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_3; }
        substitutions[28] = subtree;
        subtree = Term_ExtractSubterm(&term1, 2);
        if ((substitutions[29].atoms[0] != 0 && !Term_Equal(&substitutions[29], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_3; }
        substitutions[29] = subtree;
        if (term2.atoms[0] != 43) { goto RULE_3; }
        subtree = Term_ExtractSubterm(&term2, 1);
        if ((substitutions[28].atoms[0] != 0 && !Term_Equal(&substitutions[28], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_3; }
        substitutions[28] = subtree;
        subtree = Term_ExtractSubterm(&term2, 2);
        if ((substitutions[30].atoms[0] != 0 && !Term_Equal(&substitutions[30], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_3; }
        substitutions[30] = subtree;
        Term conclusion = {0};
        conclusion.atoms[0] = 43;
        if (!Term_OverrideSubterm(&conclusion, 1, &substitutions[30])) { goto RULE_3; }
        if (!Term_OverrideSubterm(&conclusion, 2, &substitutions[29])) { goto RULE_3; }
        Truth conclusionTruth = Truth_Induction(truth1, truth2);
        NAL_DerivedEvent(RuleTableReduce(conclusion, false), conclusionOccurrence, conclusionTruth, conclusionStamp,
                         currentTime, parentPriority, conceptPriority, occurrenceTimeOffset, validation_concept,
                         validation_cid);
    }

    RULE_3:
    {
        if (!doublePremise) { goto RULE_4; }
        Term substitutions[27 + NUM_ELEMENTS(Narsese_RuleTableVars)] = {0};
        Term subtree = {0};
        if (term1.atoms[0] != 43) { goto RULE_4; }
        subtree = Term_ExtractSubterm(&term1, 1);
        if ((substitutions[28].atoms[0] != 0 && !Term_Equal(&substitutions[28], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_4; }
        substitutions[28] = subtree;
        subtree = Term_ExtractSubterm(&term1, 2);
        if ((substitutions[30].atoms[0] != 0 && !Term_Equal(&substitutions[30], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_4; }
        substitutions[30] = subtree;
        if (term2.atoms[0] != 43) { goto RULE_4; }
        subtree = Term_ExtractSubterm(&term2, 1);
        if ((substitutions[28].atoms[0] != 0 && !Term_Equal(&substitutions[28], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_4; }
        substitutions[28] = subtree;
        subtree = Term_ExtractSubterm(&term2, 2);
        if ((substitutions[29].atoms[0] != 0 && !Term_Equal(&substitutions[29], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_4; }
        substitutions[29] = subtree;
        Term conclusion = {0};
        conclusion.atoms[0] = 43;
        if (!Term_OverrideSubterm(&conclusion, 1, &substitutions[30])) { goto RULE_4; }
        if (!Term_OverrideSubterm(&conclusion, 2, &substitutions[29])) { goto RULE_4; }
        Truth conclusionTruth = Truth_Induction(truth2, truth1);
        NAL_DerivedEvent(RuleTableReduce(conclusion, false), conclusionOccurrence, conclusionTruth, conclusionStamp,
                         currentTime, parentPriority, conceptPriority, occurrenceTimeOffset, validation_concept,
                         validation_cid);
    }

    RULE_4:
    {
        if (!doublePremise) { goto RULE_5; }
        Term substitutions[27 + NUM_ELEMENTS(Narsese_RuleTableVars)] = {0};
        Term subtree = {0};
        if (term1.atoms[0] != 43) { goto RULE_5; }
        subtree = Term_ExtractSubterm(&term1, 1);
        if ((substitutions[28].atoms[0] != 0 && !Term_Equal(&substitutions[28], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_5; }
        substitutions[28] = subtree;
        subtree = Term_ExtractSubterm(&term1, 2);
        if ((substitutions[30].atoms[0] != 0 && !Term_Equal(&substitutions[30], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_5; }
        substitutions[30] = subtree;
        if (term2.atoms[0] != 43) { goto RULE_5; }
        subtree = Term_ExtractSubterm(&term2, 1);
        if ((substitutions[29].atoms[0] != 0 && !Term_Equal(&substitutions[29], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_5; }
        substitutions[29] = subtree;
        subtree = Term_ExtractSubterm(&term2, 2);
        if ((substitutions[30].atoms[0] != 0 && !Term_Equal(&substitutions[30], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_5; }
        substitutions[30] = subtree;
        Term conclusion = {0};
        conclusion.atoms[0] = 43;
        if (!Term_OverrideSubterm(&conclusion, 1, &substitutions[29])) { goto RULE_5; }
        if (!Term_OverrideSubterm(&conclusion, 2, &substitutions[28])) { goto RULE_5; }
        Truth conclusionTruth = Truth_Abduction(truth1, truth2);
        NAL_DerivedEvent(RuleTableReduce(conclusion, false), conclusionOccurrence, conclusionTruth, conclusionStamp,
                         currentTime, parentPriority, conceptPriority, occurrenceTimeOffset, validation_concept,
                         validation_cid);
    }

    RULE_5:
    {
        if (!doublePremise) { goto RULE_6; }
        Term substitutions[27 + NUM_ELEMENTS(Narsese_RuleTableVars)] = {0};
        Term subtree = {0};
        if (term1.atoms[0] != 43) { goto RULE_6; }
        subtree = Term_ExtractSubterm(&term1, 1);
        if ((substitutions[29].atoms[0] != 0 && !Term_Equal(&substitutions[29], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_6; }
        substitutions[29] = subtree;
        subtree = Term_ExtractSubterm(&term1, 2);
        if ((substitutions[30].atoms[0] != 0 && !Term_Equal(&substitutions[30], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_6; }
        substitutions[30] = subtree;
        if (term2.atoms[0] != 43) { goto RULE_6; }
        subtree = Term_ExtractSubterm(&term2, 1);
        if ((substitutions[28].atoms[0] != 0 && !Term_Equal(&substitutions[28], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_6; }
        substitutions[28] = subtree;
        subtree = Term_ExtractSubterm(&term2, 2);
        if ((substitutions[30].atoms[0] != 0 && !Term_Equal(&substitutions[30], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_6; }
        substitutions[30] = subtree;
        Term conclusion = {0};
        conclusion.atoms[0] = 43;
        if (!Term_OverrideSubterm(&conclusion, 1, &substitutions[29])) { goto RULE_6; }
        if (!Term_OverrideSubterm(&conclusion, 2, &substitutions[28])) { goto RULE_6; }
        Truth conclusionTruth = Truth_Abduction(truth2, truth1);
        NAL_DerivedEvent(RuleTableReduce(conclusion, false), conclusionOccurrence, conclusionTruth, conclusionStamp,
                         currentTime, parentPriority, conceptPriority, occurrenceTimeOffset, validation_concept,
                         validation_cid);
    }

    RULE_6:
    {
        if (!doublePremise) { goto RULE_7; }
        Term substitutions[27 + NUM_ELEMENTS(Narsese_RuleTableVars)] = {0};
        Term subtree = {0};
        if (term1.atoms[0] != 43) { goto RULE_7; }
        subtree = Term_ExtractSubterm(&term1, 1);
        if ((substitutions[28].atoms[0] != 0 && !Term_Equal(&substitutions[28], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_7; }
        substitutions[28] = subtree;
        subtree = Term_ExtractSubterm(&term1, 2);
        if ((substitutions[29].atoms[0] != 0 && !Term_Equal(&substitutions[29], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_7; }
        substitutions[29] = subtree;
        if (term2.atoms[0] != 43) { goto RULE_7; }
        subtree = Term_ExtractSubterm(&term2, 1);
        if ((substitutions[29].atoms[0] != 0 && !Term_Equal(&substitutions[29], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_7; }
        substitutions[29] = subtree;
        subtree = Term_ExtractSubterm(&term2, 2);
        if ((substitutions[30].atoms[0] != 0 && !Term_Equal(&substitutions[30], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_7; }
        substitutions[30] = subtree;
        Term conclusion = {0};
        conclusion.atoms[0] = 43;
        if (!Term_OverrideSubterm(&conclusion, 1, &substitutions[30])) { goto RULE_7; }
        if (!Term_OverrideSubterm(&conclusion, 2, &substitutions[28])) { goto RULE_7; }
        Truth conclusionTruth = Truth_Exemplification(truth1, truth2);
        NAL_DerivedEvent(RuleTableReduce(conclusion, false), conclusionOccurrence, conclusionTruth, conclusionStamp,
                         currentTime, parentPriority, conceptPriority, occurrenceTimeOffset, validation_concept,
                         validation_cid);
    }

    RULE_7:
    {
        if (!doublePremise) { goto RULE_8; }
        Term substitutions[27 + NUM_ELEMENTS(Narsese_RuleTableVars)] = {0};
        Term subtree = {0};
        if (term1.atoms[0] != 43) { goto RULE_8; }
        subtree = Term_ExtractSubterm(&term1, 1);
        if ((substitutions[29].atoms[0] != 0 && !Term_Equal(&substitutions[29], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_8; }
        substitutions[29] = subtree;
        subtree = Term_ExtractSubterm(&term1, 2);
        if ((substitutions[30].atoms[0] != 0 && !Term_Equal(&substitutions[30], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_8; }
        substitutions[30] = subtree;
        if (term2.atoms[0] != 43) { goto RULE_8; }
        subtree = Term_ExtractSubterm(&term2, 1);
        if ((substitutions[28].atoms[0] != 0 && !Term_Equal(&substitutions[28], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_8; }
        substitutions[28] = subtree;
        subtree = Term_ExtractSubterm(&term2, 2);
        if ((substitutions[29].atoms[0] != 0 && !Term_Equal(&substitutions[29], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_8; }
        substitutions[29] = subtree;
        Term conclusion = {0};
        conclusion.atoms[0] = 43;
        if (!Term_OverrideSubterm(&conclusion, 1, &substitutions[30])) { goto RULE_8; }
        if (!Term_OverrideSubterm(&conclusion, 2, &substitutions[28])) { goto RULE_8; }
        Truth conclusionTruth = Truth_Exemplification(truth2, truth1);
        NAL_DerivedEvent(RuleTableReduce(conclusion, false), conclusionOccurrence, conclusionTruth, conclusionStamp,
                         currentTime, parentPriority, conceptPriority, occurrenceTimeOffset, validation_concept,
                         validation_cid);
    }

    RULE_8:
    {
        if (doublePremise) { goto RULE_9; }
        Term substitutions[27 + NUM_ELEMENTS(Narsese_RuleTableVars)] = {0};
        Term subtree = {0};
        if (term1.atoms[0] != 44) { goto RULE_9; }
        subtree = Term_ExtractSubterm(&term1, 1);
        if ((substitutions[33].atoms[0] != 0 && !Term_Equal(&substitutions[33], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_9; }
        substitutions[33] = subtree;
        subtree = Term_ExtractSubterm(&term1, 2);
        if ((substitutions[34].atoms[0] != 0 && !Term_Equal(&substitutions[34], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_9; }
        substitutions[34] = subtree;
        Term conclusion = {0};
        conclusion.atoms[0] = 44;
        if (!Term_OverrideSubterm(&conclusion, 1, &substitutions[34])) { goto RULE_9; }
        if (!Term_OverrideSubterm(&conclusion, 2, &substitutions[33])) { goto RULE_9; }
        Truth conclusionTruth = Truth_StructuralDeduction(truth1, truth2);
        NAL_DerivedEvent(RuleTableReduce(conclusion, false), conclusionOccurrence, conclusionTruth, conclusionStamp,
                         currentTime, parentPriority, conceptPriority, occurrenceTimeOffset, validation_concept,
                         validation_cid);
    }

    RULE_9:
    {
        if (doublePremise) { goto RULE_10; }
        Term substitutions[27 + NUM_ELEMENTS(Narsese_RuleTableVars)] = {0};
        Term subtree = {0};
        if (term1.atoms[0] != 43) { goto RULE_10; }
        subtree = Term_ExtractSubterm(&term1, 1);
        if ((substitutions[33].atoms[0] != 0 && !Term_Equal(&substitutions[33], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_10; }
        substitutions[33] = subtree;
        if (term1.atoms[2] != 47) { goto RULE_10; }
        subtree = Term_ExtractSubterm(&term1, 5);
        if ((substitutions[34].atoms[0] != 0 && !Term_Equal(&substitutions[34], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_10; }
        substitutions[34] = subtree;
        if (term1.atoms[6] != 38) { goto RULE_10; }
        Term conclusion = {0};
        conclusion.atoms[0] = 44;
        if (!Term_OverrideSubterm(&conclusion, 1, &substitutions[33])) { goto RULE_10; }
        conclusion.atoms[2] = 47;
        if (!Term_OverrideSubterm(&conclusion, 5, &substitutions[34])) { goto RULE_10; }
        conclusion.atoms[6] = 38;
        Truth conclusionTruth = Truth_StructuralDeduction(truth1, truth2);
        NAL_DerivedEvent(RuleTableReduce(conclusion, false), conclusionOccurrence, conclusionTruth, conclusionStamp,
                         currentTime, parentPriority, conceptPriority, occurrenceTimeOffset, validation_concept,
                         validation_cid);
    }

    RULE_10:
    {
        if (doublePremise) { goto RULE_11; }
        Term substitutions[27 + NUM_ELEMENTS(Narsese_RuleTableVars)] = {0};
        Term subtree = {0};
        if (term1.atoms[0] != 43) { goto RULE_11; }
        if (term1.atoms[1] != 46) { goto RULE_11; }
        subtree = Term_ExtractSubterm(&term1, 2);
        if ((substitutions[34].atoms[0] != 0 && !Term_Equal(&substitutions[34], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_11; }
        substitutions[34] = subtree;
        subtree = Term_ExtractSubterm(&term1, 3);
        if ((substitutions[33].atoms[0] != 0 && !Term_Equal(&substitutions[33], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_11; }
        substitutions[33] = subtree;
        if (term1.atoms[4] != 38) { goto RULE_11; }
        Term conclusion = {0};
        conclusion.atoms[0] = 44;
        conclusion.atoms[1] = 46;
        if (!Term_OverrideSubterm(&conclusion, 2, &substitutions[34])) { goto RULE_11; }
        if (!Term_OverrideSubterm(&conclusion, 3, &substitutions[33])) { goto RULE_11; }
        conclusion.atoms[4] = 38;
        Truth conclusionTruth = Truth_StructuralDeduction(truth1, truth2);
        NAL_DerivedEvent(RuleTableReduce(conclusion, false), conclusionOccurrence, conclusionTruth, conclusionStamp,
                         currentTime, parentPriority, conceptPriority, occurrenceTimeOffset, validation_concept,
                         validation_cid);
    }

    RULE_11:
    {
        if (!doublePremise) { goto RULE_12; }
        Term substitutions[27 + NUM_ELEMENTS(Narsese_RuleTableVars)] = {0};
        Term subtree = {0};
        if (term1.atoms[0] != 43) { goto RULE_12; }
        subtree = Term_ExtractSubterm(&term1, 1);
        if ((substitutions[34].atoms[0] != 0 && !Term_Equal(&substitutions[34], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_12; }
        substitutions[34] = subtree;
        subtree = Term_ExtractSubterm(&term1, 2);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_12; }
        substitutions[31] = subtree;
        if (term2.atoms[0] != 43) { goto RULE_12; }
        subtree = Term_ExtractSubterm(&term2, 1);
        if ((substitutions[33].atoms[0] != 0 && !Term_Equal(&substitutions[33], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_12; }
        substitutions[33] = subtree;
        subtree = Term_ExtractSubterm(&term2, 2);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_12; }
        substitutions[31] = subtree;
        Term conclusion = {0};
        conclusion.atoms[0] = 44;
        if (!Term_OverrideSubterm(&conclusion, 1, &substitutions[33])) { goto RULE_12; }
        if (!Term_OverrideSubterm(&conclusion, 2, &substitutions[34])) { goto RULE_12; }
        Truth conclusionTruth = Truth_Comparison(truth1, truth2);
        NAL_DerivedEvent(RuleTableReduce(conclusion, false), conclusionOccurrence, conclusionTruth, conclusionStamp,
                         currentTime, parentPriority, conceptPriority, occurrenceTimeOffset, validation_concept,
                         validation_cid);
    }

    RULE_12:
    {
        if (!doublePremise) { goto RULE_13; }
        Term substitutions[27 + NUM_ELEMENTS(Narsese_RuleTableVars)] = {0};
        Term subtree = {0};
        if (term1.atoms[0] != 43) { goto RULE_13; }
        subtree = Term_ExtractSubterm(&term1, 1);
        if ((substitutions[33].atoms[0] != 0 && !Term_Equal(&substitutions[33], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_13; }
        substitutions[33] = subtree;
        subtree = Term_ExtractSubterm(&term1, 2);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_13; }
        substitutions[31] = subtree;
        if (term2.atoms[0] != 43) { goto RULE_13; }
        subtree = Term_ExtractSubterm(&term2, 1);
        if ((substitutions[34].atoms[0] != 0 && !Term_Equal(&substitutions[34], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_13; }
        substitutions[34] = subtree;
        subtree = Term_ExtractSubterm(&term2, 2);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_13; }
        substitutions[31] = subtree;
        Term conclusion = {0};
        conclusion.atoms[0] = 44;
        if (!Term_OverrideSubterm(&conclusion, 1, &substitutions[33])) { goto RULE_13; }
        if (!Term_OverrideSubterm(&conclusion, 2, &substitutions[34])) { goto RULE_13; }
        Truth conclusionTruth = Truth_Comparison(truth2, truth1);
        NAL_DerivedEvent(RuleTableReduce(conclusion, false), conclusionOccurrence, conclusionTruth, conclusionStamp,
                         currentTime, parentPriority, conceptPriority, occurrenceTimeOffset, validation_concept,
                         validation_cid);
    }

    RULE_13:
    {
        if (!doublePremise) { goto RULE_14; }
        Term substitutions[27 + NUM_ELEMENTS(Narsese_RuleTableVars)] = {0};
        Term subtree = {0};
        if (term1.atoms[0] != 43) { goto RULE_14; }
        subtree = Term_ExtractSubterm(&term1, 1);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_14; }
        substitutions[31] = subtree;
        subtree = Term_ExtractSubterm(&term1, 2);
        if ((substitutions[34].atoms[0] != 0 && !Term_Equal(&substitutions[34], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_14; }
        substitutions[34] = subtree;
        if (term2.atoms[0] != 43) { goto RULE_14; }
        subtree = Term_ExtractSubterm(&term2, 1);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_14; }
        substitutions[31] = subtree;
        subtree = Term_ExtractSubterm(&term2, 2);
        if ((substitutions[33].atoms[0] != 0 && !Term_Equal(&substitutions[33], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_14; }
        substitutions[33] = subtree;
        Term conclusion = {0};
        conclusion.atoms[0] = 44;
        if (!Term_OverrideSubterm(&conclusion, 1, &substitutions[33])) { goto RULE_14; }
        if (!Term_OverrideSubterm(&conclusion, 2, &substitutions[34])) { goto RULE_14; }
        Truth conclusionTruth = Truth_Comparison(truth1, truth2);
        NAL_DerivedEvent(RuleTableReduce(conclusion, false), conclusionOccurrence, conclusionTruth, conclusionStamp,
                         currentTime, parentPriority, conceptPriority, occurrenceTimeOffset, validation_concept,
                         validation_cid);
    }

    RULE_14:
    {
        if (!doublePremise) { goto RULE_15; }
        Term substitutions[27 + NUM_ELEMENTS(Narsese_RuleTableVars)] = {0};
        Term subtree = {0};
        if (term1.atoms[0] != 43) { goto RULE_15; }
        subtree = Term_ExtractSubterm(&term1, 1);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_15; }
        substitutions[31] = subtree;
        subtree = Term_ExtractSubterm(&term1, 2);
        if ((substitutions[33].atoms[0] != 0 && !Term_Equal(&substitutions[33], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_15; }
        substitutions[33] = subtree;
        if (term2.atoms[0] != 43) { goto RULE_15; }
        subtree = Term_ExtractSubterm(&term2, 1);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_15; }
        substitutions[31] = subtree;
        subtree = Term_ExtractSubterm(&term2, 2);
        if ((substitutions[34].atoms[0] != 0 && !Term_Equal(&substitutions[34], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_15; }
        substitutions[34] = subtree;
        Term conclusion = {0};
        conclusion.atoms[0] = 44;
        if (!Term_OverrideSubterm(&conclusion, 1, &substitutions[33])) { goto RULE_15; }
        if (!Term_OverrideSubterm(&conclusion, 2, &substitutions[34])) { goto RULE_15; }
        Truth conclusionTruth = Truth_Comparison(truth2, truth1);
        NAL_DerivedEvent(RuleTableReduce(conclusion, false), conclusionOccurrence, conclusionTruth, conclusionStamp,
                         currentTime, parentPriority, conceptPriority, occurrenceTimeOffset, validation_concept,
                         validation_cid);
    }

    RULE_15:
    {
        if (!doublePremise) { goto RULE_16; }
        Term substitutions[27 + NUM_ELEMENTS(Narsese_RuleTableVars)] = {0};
        Term subtree = {0};
        if (term1.atoms[0] != 43) { goto RULE_16; }
        subtree = Term_ExtractSubterm(&term1, 1);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_16; }
        substitutions[31] = subtree;
        subtree = Term_ExtractSubterm(&term1, 2);
        if ((substitutions[34].atoms[0] != 0 && !Term_Equal(&substitutions[34], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_16; }
        substitutions[34] = subtree;
        if (term2.atoms[0] != 44) { goto RULE_16; }
        subtree = Term_ExtractSubterm(&term2, 1);
        if ((substitutions[33].atoms[0] != 0 && !Term_Equal(&substitutions[33], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_16; }
        substitutions[33] = subtree;
        subtree = Term_ExtractSubterm(&term2, 2);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_16; }
        substitutions[31] = subtree;
        Term conclusion = {0};
        conclusion.atoms[0] = 43;
        if (!Term_OverrideSubterm(&conclusion, 1, &substitutions[33])) { goto RULE_16; }
        if (!Term_OverrideSubterm(&conclusion, 2, &substitutions[34])) { goto RULE_16; }
        Truth conclusionTruth = Truth_Analogy(truth1, truth2);
        NAL_DerivedEvent(RuleTableReduce(conclusion, false), conclusionOccurrence, conclusionTruth, conclusionStamp,
                         currentTime, parentPriority, conceptPriority, occurrenceTimeOffset, validation_concept,
                         validation_cid);
    }

    RULE_16:
    {
        if (!doublePremise) { goto RULE_17; }
        Term substitutions[27 + NUM_ELEMENTS(Narsese_RuleTableVars)] = {0};
        Term subtree = {0};
        if (term1.atoms[0] != 44) { goto RULE_17; }
        subtree = Term_ExtractSubterm(&term1, 1);
        if ((substitutions[33].atoms[0] != 0 && !Term_Equal(&substitutions[33], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_17; }
        substitutions[33] = subtree;
        subtree = Term_ExtractSubterm(&term1, 2);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_17; }
        substitutions[31] = subtree;
        if (term2.atoms[0] != 43) { goto RULE_17; }
        subtree = Term_ExtractSubterm(&term2, 1);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_17; }
        substitutions[31] = subtree;
        subtree = Term_ExtractSubterm(&term2, 2);
        if ((substitutions[34].atoms[0] != 0 && !Term_Equal(&substitutions[34], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_17; }
        substitutions[34] = subtree;
        Term conclusion = {0};
        conclusion.atoms[0] = 43;
        if (!Term_OverrideSubterm(&conclusion, 1, &substitutions[33])) { goto RULE_17; }
        if (!Term_OverrideSubterm(&conclusion, 2, &substitutions[34])) { goto RULE_17; }
        Truth conclusionTruth = Truth_Analogy(truth2, truth1);
        NAL_DerivedEvent(RuleTableReduce(conclusion, false), conclusionOccurrence, conclusionTruth, conclusionStamp,
                         currentTime, parentPriority, conceptPriority, occurrenceTimeOffset, validation_concept,
                         validation_cid);
    }

    RULE_17:
    {
        if (!doublePremise) { goto RULE_18; }
        Term substitutions[27 + NUM_ELEMENTS(Narsese_RuleTableVars)] = {0};
        Term subtree = {0};
        if (term1.atoms[0] != 43) { goto RULE_18; }
        subtree = Term_ExtractSubterm(&term1, 1);
        if ((substitutions[34].atoms[0] != 0 && !Term_Equal(&substitutions[34], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_18; }
        substitutions[34] = subtree;
        subtree = Term_ExtractSubterm(&term1, 2);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_18; }
        substitutions[31] = subtree;
        if (term2.atoms[0] != 44) { goto RULE_18; }
        subtree = Term_ExtractSubterm(&term2, 1);
        if ((substitutions[33].atoms[0] != 0 && !Term_Equal(&substitutions[33], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_18; }
        substitutions[33] = subtree;
        subtree = Term_ExtractSubterm(&term2, 2);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_18; }
        substitutions[31] = subtree;
        Term conclusion = {0};
        conclusion.atoms[0] = 43;
        if (!Term_OverrideSubterm(&conclusion, 1, &substitutions[34])) { goto RULE_18; }
        if (!Term_OverrideSubterm(&conclusion, 2, &substitutions[33])) { goto RULE_18; }
        Truth conclusionTruth = Truth_Analogy(truth1, truth2);
        NAL_DerivedEvent(RuleTableReduce(conclusion, false), conclusionOccurrence, conclusionTruth, conclusionStamp,
                         currentTime, parentPriority, conceptPriority, occurrenceTimeOffset, validation_concept,
                         validation_cid);
    }

    RULE_18:
    {
        if (!doublePremise) { goto RULE_19; }
        Term substitutions[27 + NUM_ELEMENTS(Narsese_RuleTableVars)] = {0};
        Term subtree = {0};
        if (term1.atoms[0] != 44) { goto RULE_19; }
        subtree = Term_ExtractSubterm(&term1, 1);
        if ((substitutions[33].atoms[0] != 0 && !Term_Equal(&substitutions[33], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_19; }
        substitutions[33] = subtree;
        subtree = Term_ExtractSubterm(&term1, 2);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_19; }
        substitutions[31] = subtree;
        if (term2.atoms[0] != 43) { goto RULE_19; }
        subtree = Term_ExtractSubterm(&term2, 1);
        if ((substitutions[34].atoms[0] != 0 && !Term_Equal(&substitutions[34], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_19; }
        substitutions[34] = subtree;
        subtree = Term_ExtractSubterm(&term2, 2);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_19; }
        substitutions[31] = subtree;
        Term conclusion = {0};
        conclusion.atoms[0] = 43;
        if (!Term_OverrideSubterm(&conclusion, 1, &substitutions[34])) { goto RULE_19; }
        if (!Term_OverrideSubterm(&conclusion, 2, &substitutions[33])) { goto RULE_19; }
        Truth conclusionTruth = Truth_Analogy(truth2, truth1);
        NAL_DerivedEvent(RuleTableReduce(conclusion, false), conclusionOccurrence, conclusionTruth, conclusionStamp,
                         currentTime, parentPriority, conceptPriority, occurrenceTimeOffset, validation_concept,
                         validation_cid);
    }

    RULE_19:
    {
        if (!doublePremise) { goto RULE_20; }
        Term substitutions[27 + NUM_ELEMENTS(Narsese_RuleTableVars)] = {0};
        Term subtree = {0};
        if (term1.atoms[0] != 43) { goto RULE_20; }
        if (term1.atoms[1] != 47) { goto RULE_20; }
        subtree = Term_ExtractSubterm(&term1, 2);
        if ((substitutions[34].atoms[0] != 0 && !Term_Equal(&substitutions[34], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_20; }
        substitutions[34] = subtree;
        subtree = Term_ExtractSubterm(&term1, 3);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_20; }
        substitutions[31] = subtree;
        if (term1.atoms[4] != 38) { goto RULE_20; }
        if (term2.atoms[0] != 44) { goto RULE_20; }
        subtree = Term_ExtractSubterm(&term2, 1);
        if ((substitutions[33].atoms[0] != 0 && !Term_Equal(&substitutions[33], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_20; }
        substitutions[33] = subtree;
        subtree = Term_ExtractSubterm(&term2, 2);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_20; }
        substitutions[31] = subtree;
        Term conclusion = {0};
        conclusion.atoms[0] = 43;
        conclusion.atoms[1] = 47;
        if (!Term_OverrideSubterm(&conclusion, 2, &substitutions[34])) { goto RULE_20; }
        if (!Term_OverrideSubterm(&conclusion, 3, &substitutions[33])) { goto RULE_20; }
        conclusion.atoms[4] = 38;
        Truth conclusionTruth = Truth_Analogy(truth1, truth2);
        NAL_DerivedEvent(RuleTableReduce(conclusion, false), conclusionOccurrence, conclusionTruth, conclusionStamp,
                         currentTime, parentPriority, conceptPriority, occurrenceTimeOffset, validation_concept,
                         validation_cid);
    }

    RULE_20:
    {
        if (!doublePremise) { goto RULE_21; }
        Term substitutions[27 + NUM_ELEMENTS(Narsese_RuleTableVars)] = {0};
        Term subtree = {0};
        if (term1.atoms[0] != 44) { goto RULE_21; }
        subtree = Term_ExtractSubterm(&term1, 1);
        if ((substitutions[33].atoms[0] != 0 && !Term_Equal(&substitutions[33], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_21; }
        substitutions[33] = subtree;
        subtree = Term_ExtractSubterm(&term1, 2);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_21; }
        substitutions[31] = subtree;
        if (term2.atoms[0] != 43) { goto RULE_21; }
        if (term2.atoms[1] != 47) { goto RULE_21; }
        subtree = Term_ExtractSubterm(&term2, 2);
        if ((substitutions[34].atoms[0] != 0 && !Term_Equal(&substitutions[34], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_21; }
        substitutions[34] = subtree;
        subtree = Term_ExtractSubterm(&term2, 3);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_21; }
        substitutions[31] = subtree;
        if (term2.atoms[4] != 38) { goto RULE_21; }
        Term conclusion = {0};
        conclusion.atoms[0] = 43;
        conclusion.atoms[1] = 47;
        if (!Term_OverrideSubterm(&conclusion, 2, &substitutions[34])) { goto RULE_21; }
        if (!Term_OverrideSubterm(&conclusion, 3, &substitutions[33])) { goto RULE_21; }
        conclusion.atoms[4] = 38;
        Truth conclusionTruth = Truth_Analogy(truth2, truth1);
        NAL_DerivedEvent(RuleTableReduce(conclusion, false), conclusionOccurrence, conclusionTruth, conclusionStamp,
                         currentTime, parentPriority, conceptPriority, occurrenceTimeOffset, validation_concept,
                         validation_cid);
    }

    RULE_21:
    {
        if (!doublePremise) { goto RULE_22; }
        Term substitutions[27 + NUM_ELEMENTS(Narsese_RuleTableVars)] = {0};
        Term subtree = {0};
        if (term1.atoms[0] != 43) { goto RULE_22; }
        subtree = Term_ExtractSubterm(&term1, 1);
        if ((substitutions[34].atoms[0] != 0 && !Term_Equal(&substitutions[34], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_22; }
        substitutions[34] = subtree;
        if (term1.atoms[2] != 46) { goto RULE_22; }
        subtree = Term_ExtractSubterm(&term1, 5);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_22; }
        substitutions[31] = subtree;
        if (term1.atoms[6] != 38) { goto RULE_22; }
        if (term2.atoms[0] != 44) { goto RULE_22; }
        subtree = Term_ExtractSubterm(&term2, 1);
        if ((substitutions[33].atoms[0] != 0 && !Term_Equal(&substitutions[33], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_22; }
        substitutions[33] = subtree;
        subtree = Term_ExtractSubterm(&term2, 2);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_22; }
        substitutions[31] = subtree;
        Term conclusion = {0};
        conclusion.atoms[0] = 43;
        if (!Term_OverrideSubterm(&conclusion, 1, &substitutions[34])) { goto RULE_22; }
        conclusion.atoms[2] = 46;
        if (!Term_OverrideSubterm(&conclusion, 5, &substitutions[33])) { goto RULE_22; }
        conclusion.atoms[6] = 38;
        Truth conclusionTruth = Truth_Analogy(truth1, truth2);
        NAL_DerivedEvent(RuleTableReduce(conclusion, false), conclusionOccurrence, conclusionTruth, conclusionStamp,
                         currentTime, parentPriority, conceptPriority, occurrenceTimeOffset, validation_concept,
                         validation_cid);
    }

    RULE_22:
    {
        if (!doublePremise) { goto RULE_23; }
        Term substitutions[27 + NUM_ELEMENTS(Narsese_RuleTableVars)] = {0};
        Term subtree = {0};
        if (term1.atoms[0] != 44) { goto RULE_23; }
        subtree = Term_ExtractSubterm(&term1, 1);
        if ((substitutions[33].atoms[0] != 0 && !Term_Equal(&substitutions[33], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_23; }
        substitutions[33] = subtree;
        subtree = Term_ExtractSubterm(&term1, 2);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_23; }
        substitutions[31] = subtree;
        if (term2.atoms[0] != 43) { goto RULE_23; }
        subtree = Term_ExtractSubterm(&term2, 1);
        if ((substitutions[34].atoms[0] != 0 && !Term_Equal(&substitutions[34], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_23; }
        substitutions[34] = subtree;
        if (term2.atoms[2] != 46) { goto RULE_23; }
        subtree = Term_ExtractSubterm(&term2, 5);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_23; }
        substitutions[31] = subtree;
        if (term2.atoms[6] != 38) { goto RULE_23; }
        Term conclusion = {0};
        conclusion.atoms[0] = 43;
        if (!Term_OverrideSubterm(&conclusion, 1, &substitutions[34])) { goto RULE_23; }
        conclusion.atoms[2] = 46;
        if (!Term_OverrideSubterm(&conclusion, 5, &substitutions[33])) { goto RULE_23; }
        conclusion.atoms[6] = 38;
        Truth conclusionTruth = Truth_Analogy(truth2, truth1);
        NAL_DerivedEvent(RuleTableReduce(conclusion, false), conclusionOccurrence, conclusionTruth, conclusionStamp,
                         currentTime, parentPriority, conceptPriority, occurrenceTimeOffset, validation_concept,
                         validation_cid);
    }

    RULE_23:
    {
        if (!doublePremise) { goto RULE_24; }
        Term substitutions[27 + NUM_ELEMENTS(Narsese_RuleTableVars)] = {0};
        Term subtree = {0};
        if (term1.atoms[0] != 44) { goto RULE_24; }
        subtree = Term_ExtractSubterm(&term1, 1);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_24; }
        substitutions[31] = subtree;
        subtree = Term_ExtractSubterm(&term1, 2);
        if ((substitutions[34].atoms[0] != 0 && !Term_Equal(&substitutions[34], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_24; }
        substitutions[34] = subtree;
        if (term2.atoms[0] != 44) { goto RULE_24; }
        subtree = Term_ExtractSubterm(&term2, 1);
        if ((substitutions[33].atoms[0] != 0 && !Term_Equal(&substitutions[33], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_24; }
        substitutions[33] = subtree;
        subtree = Term_ExtractSubterm(&term2, 2);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_24; }
        substitutions[31] = subtree;
        Term conclusion = {0};
        conclusion.atoms[0] = 44;
        if (!Term_OverrideSubterm(&conclusion, 1, &substitutions[33])) { goto RULE_24; }
        if (!Term_OverrideSubterm(&conclusion, 2, &substitutions[34])) { goto RULE_24; }
        Truth conclusionTruth = Truth_Resemblance(truth1, truth2);
        NAL_DerivedEvent(RuleTableReduce(conclusion, false), conclusionOccurrence, conclusionTruth, conclusionStamp,
                         currentTime, parentPriority, conceptPriority, occurrenceTimeOffset, validation_concept,
                         validation_cid);
    }

    RULE_24:
    {
        if (!doublePremise) { goto RULE_25; }
        Term substitutions[27 + NUM_ELEMENTS(Narsese_RuleTableVars)] = {0};
        Term subtree = {0};
        if (term1.atoms[0] != 44) { goto RULE_25; }
        subtree = Term_ExtractSubterm(&term1, 1);
        if ((substitutions[33].atoms[0] != 0 && !Term_Equal(&substitutions[33], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_25; }
        substitutions[33] = subtree;
        subtree = Term_ExtractSubterm(&term1, 2);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_25; }
        substitutions[31] = subtree;
        if (term2.atoms[0] != 44) { goto RULE_25; }
        subtree = Term_ExtractSubterm(&term2, 1);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_25; }
        substitutions[31] = subtree;
        subtree = Term_ExtractSubterm(&term2, 2);
        if ((substitutions[34].atoms[0] != 0 && !Term_Equal(&substitutions[34], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_25; }
        substitutions[34] = subtree;
        Term conclusion = {0};
        conclusion.atoms[0] = 44;
        if (!Term_OverrideSubterm(&conclusion, 1, &substitutions[33])) { goto RULE_25; }
        if (!Term_OverrideSubterm(&conclusion, 2, &substitutions[34])) { goto RULE_25; }
        Truth conclusionTruth = Truth_Resemblance(truth2, truth1);
        NAL_DerivedEvent(RuleTableReduce(conclusion, false), conclusionOccurrence, conclusionTruth, conclusionStamp,
                         currentTime, parentPriority, conceptPriority, occurrenceTimeOffset, validation_concept,
                         validation_cid);
    }

    RULE_25:
    {
        if (doublePremise) { goto RULE_26; }
        Term substitutions[27 + NUM_ELEMENTS(Narsese_RuleTableVars)] = {0};
        Term subtree = {0};
        if (term1.atoms[0] != 44) { goto RULE_26; }
        if (term1.atoms[1] != 47) { goto RULE_26; }
        if (term1.atoms[2] != 47) { goto RULE_26; }
        subtree = Term_ExtractSubterm(&term1, 3);
        if ((substitutions[28].atoms[0] != 0 && !Term_Equal(&substitutions[28], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_26; }
        substitutions[28] = subtree;
        if (term1.atoms[4] != 38) { goto RULE_26; }
        subtree = Term_ExtractSubterm(&term1, 5);
        if ((substitutions[29].atoms[0] != 0 && !Term_Equal(&substitutions[29], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_26; }
        substitutions[29] = subtree;
        if (term1.atoms[6] != 38) { goto RULE_26; }
        Term conclusion = {0};
        conclusion.atoms[0] = 44;
        if (!Term_OverrideSubterm(&conclusion, 1, &substitutions[28])) { goto RULE_26; }
        if (!Term_OverrideSubterm(&conclusion, 2, &substitutions[29])) { goto RULE_26; }
        Truth conclusionTruth = Truth_StructuralDeduction(truth1, truth2);
        NAL_DerivedEvent(RuleTableReduce(conclusion, false), conclusionOccurrence, conclusionTruth, conclusionStamp,
                         currentTime, parentPriority, conceptPriority, occurrenceTimeOffset, validation_concept,
                         validation_cid);
    }

    RULE_26:
    {
        if (doublePremise) { goto RULE_27; }
        Term substitutions[27 + NUM_ELEMENTS(Narsese_RuleTableVars)] = {0};
        Term subtree = {0};
        if (term1.atoms[0] != 44) { goto RULE_27; }
        if (term1.atoms[1] != 46) { goto RULE_27; }
        if (term1.atoms[2] != 46) { goto RULE_27; }
        subtree = Term_ExtractSubterm(&term1, 3);
        if ((substitutions[28].atoms[0] != 0 && !Term_Equal(&substitutions[28], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_27; }
        substitutions[28] = subtree;
        if (term1.atoms[4] != 38) { goto RULE_27; }
        subtree = Term_ExtractSubterm(&term1, 5);
        if ((substitutions[29].atoms[0] != 0 && !Term_Equal(&substitutions[29], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_27; }
        substitutions[29] = subtree;
        if (term1.atoms[6] != 38) { goto RULE_27; }
        Term conclusion = {0};
        conclusion.atoms[0] = 44;
        if (!Term_OverrideSubterm(&conclusion, 1, &substitutions[28])) { goto RULE_27; }
        if (!Term_OverrideSubterm(&conclusion, 2, &substitutions[29])) { goto RULE_27; }
        Truth conclusionTruth = Truth_StructuralDeduction(truth1, truth2);
        NAL_DerivedEvent(RuleTableReduce(conclusion, false), conclusionOccurrence, conclusionTruth, conclusionStamp,
                         currentTime, parentPriority, conceptPriority, occurrenceTimeOffset, validation_concept,
                         validation_cid);
    }

    RULE_27:
    {
        if (doublePremise) { goto RULE_28; }
        Term substitutions[27 + NUM_ELEMENTS(Narsese_RuleTableVars)] = {0};
        Term subtree = {0};
        if (term1.atoms[0] != 43) { goto RULE_28; }
        if (term1.atoms[1] != 47) { goto RULE_28; }
        subtree = Term_ExtractSubterm(&term1, 2);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_28; }
        substitutions[31] = subtree;
        subtree = Term_ExtractSubterm(&term1, 3);
        if ((substitutions[28].atoms[0] != 0 && !Term_Equal(&substitutions[28], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_28; }
        substitutions[28] = subtree;
        subtree = Term_ExtractSubterm(&term1, 4);
        if ((substitutions[29].atoms[0] != 0 && !Term_Equal(&substitutions[29], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_28; }
        substitutions[29] = subtree;
        Term conclusion = {0};
        conclusion.atoms[0] = 43;
        conclusion.atoms[1] = 47;
        if (!Term_OverrideSubterm(&conclusion, 2, &substitutions[31])) { goto RULE_28; }
        if (!Term_OverrideSubterm(&conclusion, 3, &substitutions[28])) { goto RULE_28; }
        conclusion.atoms[4] = 38;
        Truth conclusionTruth = Truth_StructuralDeduction(truth1, truth2);
        NAL_DerivedEvent(RuleTableReduce(conclusion, false), conclusionOccurrence, conclusionTruth, conclusionStamp,
                         currentTime, parentPriority, conceptPriority, occurrenceTimeOffset, validation_concept,
                         validation_cid);
    }

    RULE_28:
    {
        if (doublePremise) { goto RULE_29; }
        Term substitutions[27 + NUM_ELEMENTS(Narsese_RuleTableVars)] = {0};
        Term subtree = {0};
        if (term1.atoms[0] != 43) { goto RULE_29; }
        if (term1.atoms[1] != 47) { goto RULE_29; }
        subtree = Term_ExtractSubterm(&term1, 2);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_29; }
        substitutions[31] = subtree;
        subtree = Term_ExtractSubterm(&term1, 3);
        if ((substitutions[28].atoms[0] != 0 && !Term_Equal(&substitutions[28], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_29; }
        substitutions[28] = subtree;
        subtree = Term_ExtractSubterm(&term1, 4);
        if ((substitutions[29].atoms[0] != 0 && !Term_Equal(&substitutions[29], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_29; }
        substitutions[29] = subtree;
        Term conclusion = {0};
        conclusion.atoms[0] = 43;
        conclusion.atoms[1] = 47;
        if (!Term_OverrideSubterm(&conclusion, 2, &substitutions[31])) { goto RULE_29; }
        if (!Term_OverrideSubterm(&conclusion, 3, &substitutions[29])) { goto RULE_29; }
        conclusion.atoms[4] = 38;
        Truth conclusionTruth = Truth_StructuralDeduction(truth1, truth2);
        NAL_DerivedEvent(RuleTableReduce(conclusion, false), conclusionOccurrence, conclusionTruth, conclusionStamp,
                         currentTime, parentPriority, conceptPriority, occurrenceTimeOffset, validation_concept,
                         validation_cid);
    }

    RULE_29:
    {
        if (doublePremise) { goto RULE_30; }
        Term substitutions[27 + NUM_ELEMENTS(Narsese_RuleTableVars)] = {0};
        Term subtree = {0};
        if (term1.atoms[0] != 43) { goto RULE_30; }
        subtree = Term_ExtractSubterm(&term1, 1);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_30; }
        substitutions[31] = subtree;
        if (term1.atoms[2] != 46) { goto RULE_30; }
        subtree = Term_ExtractSubterm(&term1, 5);
        if ((substitutions[28].atoms[0] != 0 && !Term_Equal(&substitutions[28], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_30; }
        substitutions[28] = subtree;
        subtree = Term_ExtractSubterm(&term1, 6);
        if ((substitutions[29].atoms[0] != 0 && !Term_Equal(&substitutions[29], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_30; }
        substitutions[29] = subtree;
        Term conclusion = {0};
        conclusion.atoms[0] = 43;
        if (!Term_OverrideSubterm(&conclusion, 1, &substitutions[31])) { goto RULE_30; }
        conclusion.atoms[2] = 46;
        if (!Term_OverrideSubterm(&conclusion, 5, &substitutions[28])) { goto RULE_30; }
        conclusion.atoms[6] = 38;
        Truth conclusionTruth = Truth_StructuralDeduction(truth1, truth2);
        NAL_DerivedEvent(RuleTableReduce(conclusion, false), conclusionOccurrence, conclusionTruth, conclusionStamp,
                         currentTime, parentPriority, conceptPriority, occurrenceTimeOffset, validation_concept,
                         validation_cid);
    }

    RULE_30:
    {
        if (doublePremise) { goto RULE_31; }
        Term substitutions[27 + NUM_ELEMENTS(Narsese_RuleTableVars)] = {0};
        Term subtree = {0};
        if (term1.atoms[0] != 43) { goto RULE_31; }
        subtree = Term_ExtractSubterm(&term1, 1);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_31; }
        substitutions[31] = subtree;
        if (term1.atoms[2] != 46) { goto RULE_31; }
        subtree = Term_ExtractSubterm(&term1, 5);
        if ((substitutions[28].atoms[0] != 0 && !Term_Equal(&substitutions[28], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_31; }
        substitutions[28] = subtree;
        subtree = Term_ExtractSubterm(&term1, 6);
        if ((substitutions[29].atoms[0] != 0 && !Term_Equal(&substitutions[29], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_31; }
        substitutions[29] = subtree;
        Term conclusion = {0};
        conclusion.atoms[0] = 43;
        if (!Term_OverrideSubterm(&conclusion, 1, &substitutions[31])) { goto RULE_31; }
        conclusion.atoms[2] = 46;
        if (!Term_OverrideSubterm(&conclusion, 5, &substitutions[29])) { goto RULE_31; }
        conclusion.atoms[6] = 38;
        Truth conclusionTruth = Truth_StructuralDeduction(truth1, truth2);
        NAL_DerivedEvent(RuleTableReduce(conclusion, false), conclusionOccurrence, conclusionTruth, conclusionStamp,
                         currentTime, parentPriority, conceptPriority, occurrenceTimeOffset, validation_concept,
                         validation_cid);
    }

    RULE_31:
    {
        if (doublePremise) { goto RULE_32; }
        Term substitutions[27 + NUM_ELEMENTS(Narsese_RuleTableVars)] = {0};
        Term subtree = {0};
        if (term1.atoms[0] != 43) { goto RULE_32; }
        if (term1.atoms[1] != 41) { goto RULE_32; }
        subtree = Term_ExtractSubterm(&term1, 2);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_32; }
        substitutions[31] = subtree;
        subtree = Term_ExtractSubterm(&term1, 3);
        if ((substitutions[33].atoms[0] != 0 && !Term_Equal(&substitutions[33], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_32; }
        substitutions[33] = subtree;
        subtree = Term_ExtractSubterm(&term1, 4);
        if ((substitutions[34].atoms[0] != 0 && !Term_Equal(&substitutions[34], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_32; }
        substitutions[34] = subtree;
        Term conclusion = {0};
        conclusion.atoms[0] = 43;
        if (!Term_OverrideSubterm(&conclusion, 1, &substitutions[33])) { goto RULE_32; }
        if (!Term_OverrideSubterm(&conclusion, 2, &substitutions[31])) { goto RULE_32; }
        Truth conclusionTruth = Truth_StructuralDeduction(truth1, truth2);
        NAL_DerivedEvent(RuleTableReduce(conclusion, false), conclusionOccurrence, conclusionTruth, conclusionStamp,
                         currentTime, parentPriority, conceptPriority, occurrenceTimeOffset, validation_concept,
                         validation_cid);
    }

    RULE_32:
    {
        if (doublePremise) { goto RULE_33; }
        Term substitutions[27 + NUM_ELEMENTS(Narsese_RuleTableVars)] = {0};
        Term subtree = {0};
        if (term1.atoms[0] != 43) { goto RULE_33; }
        subtree = Term_ExtractSubterm(&term1, 1);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_33; }
        substitutions[31] = subtree;
        if (term1.atoms[2] != 40) { goto RULE_33; }
        subtree = Term_ExtractSubterm(&term1, 5);
        if ((substitutions[33].atoms[0] != 0 && !Term_Equal(&substitutions[33], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_33; }
        substitutions[33] = subtree;
        subtree = Term_ExtractSubterm(&term1, 6);
        if ((substitutions[34].atoms[0] != 0 && !Term_Equal(&substitutions[34], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_33; }
        substitutions[34] = subtree;
        Term conclusion = {0};
        conclusion.atoms[0] = 43;
        if (!Term_OverrideSubterm(&conclusion, 1, &substitutions[31])) { goto RULE_33; }
        if (!Term_OverrideSubterm(&conclusion, 2, &substitutions[33])) { goto RULE_33; }
        Truth conclusionTruth = Truth_StructuralDeduction(truth1, truth2);
        NAL_DerivedEvent(RuleTableReduce(conclusion, false), conclusionOccurrence, conclusionTruth, conclusionStamp,
                         currentTime, parentPriority, conceptPriority, occurrenceTimeOffset, validation_concept,
                         validation_cid);
    }

    RULE_33:
    {
        if (doublePremise) { goto RULE_34; }
        Term substitutions[27 + NUM_ELEMENTS(Narsese_RuleTableVars)] = {0};
        Term subtree = {0};
        if (term1.atoms[0] != 43) { goto RULE_34; }
        if (term1.atoms[1] != 41) { goto RULE_34; }
        subtree = Term_ExtractSubterm(&term1, 2);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_34; }
        substitutions[31] = subtree;
        subtree = Term_ExtractSubterm(&term1, 3);
        if ((substitutions[33].atoms[0] != 0 && !Term_Equal(&substitutions[33], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_34; }
        substitutions[33] = subtree;
        subtree = Term_ExtractSubterm(&term1, 4);
        if ((substitutions[34].atoms[0] != 0 && !Term_Equal(&substitutions[34], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_34; }
        substitutions[34] = subtree;
        Term conclusion = {0};
        conclusion.atoms[0] = 43;
        if (!Term_OverrideSubterm(&conclusion, 1, &substitutions[34])) { goto RULE_34; }
        if (!Term_OverrideSubterm(&conclusion, 2, &substitutions[31])) { goto RULE_34; }
        Truth conclusionTruth = Truth_StructuralDeduction(truth1, truth2);
        NAL_DerivedEvent(RuleTableReduce(conclusion, false), conclusionOccurrence, conclusionTruth, conclusionStamp,
                         currentTime, parentPriority, conceptPriority, occurrenceTimeOffset, validation_concept,
                         validation_cid);
    }

    RULE_34:
    {
        if (doublePremise) { goto RULE_35; }
        Term substitutions[27 + NUM_ELEMENTS(Narsese_RuleTableVars)] = {0};
        Term subtree = {0};
        if (term1.atoms[0] != 43) { goto RULE_35; }
        subtree = Term_ExtractSubterm(&term1, 1);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_35; }
        substitutions[31] = subtree;
        if (term1.atoms[2] != 40) { goto RULE_35; }
        subtree = Term_ExtractSubterm(&term1, 5);
        if ((substitutions[33].atoms[0] != 0 && !Term_Equal(&substitutions[33], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_35; }
        substitutions[33] = subtree;
        subtree = Term_ExtractSubterm(&term1, 6);
        if ((substitutions[34].atoms[0] != 0 && !Term_Equal(&substitutions[34], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_35; }
        substitutions[34] = subtree;
        Term conclusion = {0};
        conclusion.atoms[0] = 43;
        if (!Term_OverrideSubterm(&conclusion, 1, &substitutions[31])) { goto RULE_35; }
        if (!Term_OverrideSubterm(&conclusion, 2, &substitutions[34])) { goto RULE_35; }
        Truth conclusionTruth = Truth_StructuralDeduction(truth1, truth2);
        NAL_DerivedEvent(RuleTableReduce(conclusion, false), conclusionOccurrence, conclusionTruth, conclusionStamp,
                         currentTime, parentPriority, conceptPriority, occurrenceTimeOffset, validation_concept,
                         validation_cid);
    }

    RULE_35:
    {
        if (doublePremise) { goto RULE_36; }
        Term substitutions[27 + NUM_ELEMENTS(Narsese_RuleTableVars)] = {0};
        Term subtree = {0};
        if (term1.atoms[0] != 43) { goto RULE_36; }
        if (term1.atoms[1] != 54) { goto RULE_36; }
        subtree = Term_ExtractSubterm(&term1, 2);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_36; }
        substitutions[31] = subtree;
        subtree = Term_ExtractSubterm(&term1, 3);
        if ((substitutions[28].atoms[0] != 0 && !Term_Equal(&substitutions[28], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_36; }
        substitutions[28] = subtree;
        subtree = Term_ExtractSubterm(&term1, 4);
        if ((substitutions[33].atoms[0] != 0 && !Term_Equal(&substitutions[33], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_36; }
        substitutions[33] = subtree;
        Term conclusion = {0};
        conclusion.atoms[0] = 43;
        if (!Term_OverrideSubterm(&conclusion, 1, &substitutions[28])) { goto RULE_36; }
        if (!Term_OverrideSubterm(&conclusion, 2, &substitutions[31])) { goto RULE_36; }
        Truth conclusionTruth = Truth_StructuralDeduction(truth1, truth2);
        NAL_DerivedEvent(RuleTableReduce(conclusion, false), conclusionOccurrence, conclusionTruth, conclusionStamp,
                         currentTime, parentPriority, conceptPriority, occurrenceTimeOffset, validation_concept,
                         validation_cid);
    }

    RULE_36:
    {
        if (doublePremise) { goto RULE_37; }
        Term substitutions[27 + NUM_ELEMENTS(Narsese_RuleTableVars)] = {0};
        Term subtree = {0};
        if (term1.atoms[0] != 43) { goto RULE_37; }
        subtree = Term_ExtractSubterm(&term1, 1);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_37; }
        substitutions[31] = subtree;
        if (term1.atoms[2] != 51) { goto RULE_37; }
        subtree = Term_ExtractSubterm(&term1, 5);
        if ((substitutions[29].atoms[0] != 0 && !Term_Equal(&substitutions[29], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_37; }
        substitutions[29] = subtree;
        subtree = Term_ExtractSubterm(&term1, 6);
        if ((substitutions[33].atoms[0] != 0 && !Term_Equal(&substitutions[33], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_37; }
        substitutions[33] = subtree;
        Term conclusion = {0};
        conclusion.atoms[0] = 43;
        if (!Term_OverrideSubterm(&conclusion, 1, &substitutions[31])) { goto RULE_37; }
        if (!Term_OverrideSubterm(&conclusion, 2, &substitutions[29])) { goto RULE_37; }
        Truth conclusionTruth = Truth_StructuralDeduction(truth1, truth2);
        NAL_DerivedEvent(RuleTableReduce(conclusion, false), conclusionOccurrence, conclusionTruth, conclusionStamp,
                         currentTime, parentPriority, conceptPriority, occurrenceTimeOffset, validation_concept,
                         validation_cid);
    }

    RULE_37:
    {
        if (doublePremise) { goto RULE_38; }
        Term substitutions[27 + NUM_ELEMENTS(Narsese_RuleTableVars)] = {0};
        Term subtree = {0};
        if (term1.atoms[0] != 43) { goto RULE_38; }
        if (term1.atoms[1] != 54) { goto RULE_38; }
        subtree = Term_ExtractSubterm(&term1, 2);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_38; }
        substitutions[31] = subtree;
        subtree = Term_ExtractSubterm(&term1, 3);
        if ((substitutions[28].atoms[0] != 0 && !Term_Equal(&substitutions[28], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_38; }
        substitutions[28] = subtree;
        subtree = Term_ExtractSubterm(&term1, 4);
        if ((substitutions[33].atoms[0] != 0 && !Term_Equal(&substitutions[33], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_38; }
        substitutions[33] = subtree;
        Term conclusion = {0};
        conclusion.atoms[0] = 43;
        if (!Term_OverrideSubterm(&conclusion, 1, &substitutions[33])) { goto RULE_38; }
        if (!Term_OverrideSubterm(&conclusion, 2, &substitutions[31])) { goto RULE_38; }
        Truth conclusionTruth = Truth_StructuralDeductionNegated(truth1, truth2);
        NAL_DerivedEvent(RuleTableReduce(conclusion, false), conclusionOccurrence, conclusionTruth, conclusionStamp,
                         currentTime, parentPriority, conceptPriority, occurrenceTimeOffset, validation_concept,
                         validation_cid);
    }

    RULE_38:
    {
        if (doublePremise) { goto RULE_39; }
        Term substitutions[27 + NUM_ELEMENTS(Narsese_RuleTableVars)] = {0};
        Term subtree = {0};
        if (term1.atoms[0] != 43) { goto RULE_39; }
        subtree = Term_ExtractSubterm(&term1, 1);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_39; }
        substitutions[31] = subtree;
        if (term1.atoms[2] != 51) { goto RULE_39; }
        subtree = Term_ExtractSubterm(&term1, 5);
        if ((substitutions[29].atoms[0] != 0 && !Term_Equal(&substitutions[29], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_39; }
        substitutions[29] = subtree;
        subtree = Term_ExtractSubterm(&term1, 6);
        if ((substitutions[33].atoms[0] != 0 && !Term_Equal(&substitutions[33], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_39; }
        substitutions[33] = subtree;
        Term conclusion = {0};
        conclusion.atoms[0] = 43;
        if (!Term_OverrideSubterm(&conclusion, 1, &substitutions[31])) { goto RULE_39; }
        if (!Term_OverrideSubterm(&conclusion, 2, &substitutions[33])) { goto RULE_39; }
        Truth conclusionTruth = Truth_StructuralDeductionNegated(truth1, truth2);
        NAL_DerivedEvent(RuleTableReduce(conclusion, false), conclusionOccurrence, conclusionTruth, conclusionStamp,
                         currentTime, parentPriority, conceptPriority, occurrenceTimeOffset, validation_concept,
                         validation_cid);
    }

    RULE_39:
    {
        if (!doublePremise) { goto RULE_40; }
        Term substitutions[27 + NUM_ELEMENTS(Narsese_RuleTableVars)] = {0};
        Term subtree = {0};
        if (term1.atoms[0] != 43) { goto RULE_40; }
        subtree = Term_ExtractSubterm(&term1, 1);
        if ((substitutions[34].atoms[0] != 0 && !Term_Equal(&substitutions[34], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_40; }
        substitutions[34] = subtree;
        subtree = Term_ExtractSubterm(&term1, 2);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_40; }
        substitutions[31] = subtree;
        if (term2.atoms[0] != 43) { goto RULE_40; }
        subtree = Term_ExtractSubterm(&term2, 1);
        if ((substitutions[33].atoms[0] != 0 && !Term_Equal(&substitutions[33], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_40; }
        substitutions[33] = subtree;
        subtree = Term_ExtractSubterm(&term2, 2);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_40; }
        substitutions[31] = subtree;
        Term conclusion = {0};
        conclusion.atoms[0] = 43;
        conclusion.atoms[1] = 41;
        if (!Term_OverrideSubterm(&conclusion, 2, &substitutions[31])) { goto RULE_40; }
        if (!Term_OverrideSubterm(&conclusion, 3, &substitutions[34])) { goto RULE_40; }
        if (!Term_OverrideSubterm(&conclusion, 4, &substitutions[33])) { goto RULE_40; }
        Truth conclusionTruth = Truth_Intersection(truth1, truth2);
        NAL_DerivedEvent(RuleTableReduce(conclusion, false), conclusionOccurrence, conclusionTruth, conclusionStamp,
                         currentTime, parentPriority, conceptPriority, occurrenceTimeOffset, validation_concept,
                         validation_cid);
    }

    RULE_40:
    {
        if (!doublePremise) { goto RULE_41; }
        Term substitutions[27 + NUM_ELEMENTS(Narsese_RuleTableVars)] = {0};
        Term subtree = {0};
        if (term1.atoms[0] != 43) { goto RULE_41; }
        subtree = Term_ExtractSubterm(&term1, 1);
        if ((substitutions[33].atoms[0] != 0 && !Term_Equal(&substitutions[33], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_41; }
        substitutions[33] = subtree;
        subtree = Term_ExtractSubterm(&term1, 2);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_41; }
        substitutions[31] = subtree;
        if (term2.atoms[0] != 43) { goto RULE_41; }
        subtree = Term_ExtractSubterm(&term2, 1);
        if ((substitutions[34].atoms[0] != 0 && !Term_Equal(&substitutions[34], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_41; }
        substitutions[34] = subtree;
        subtree = Term_ExtractSubterm(&term2, 2);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_41; }
        substitutions[31] = subtree;
        Term conclusion = {0};
        conclusion.atoms[0] = 43;
        conclusion.atoms[1] = 41;
        if (!Term_OverrideSubterm(&conclusion, 2, &substitutions[31])) { goto RULE_41; }
        if (!Term_OverrideSubterm(&conclusion, 3, &substitutions[34])) { goto RULE_41; }
        if (!Term_OverrideSubterm(&conclusion, 4, &substitutions[33])) { goto RULE_41; }
        Truth conclusionTruth = Truth_Intersection(truth2, truth1);
        NAL_DerivedEvent(RuleTableReduce(conclusion, false), conclusionOccurrence, conclusionTruth, conclusionStamp,
                         currentTime, parentPriority, conceptPriority, occurrenceTimeOffset, validation_concept,
                         validation_cid);
    }

    RULE_41:
    {
        if (!doublePremise) { goto RULE_42; }
        Term substitutions[27 + NUM_ELEMENTS(Narsese_RuleTableVars)] = {0};
        Term subtree = {0};
        if (term1.atoms[0] != 43) { goto RULE_42; }
        subtree = Term_ExtractSubterm(&term1, 1);
        if ((substitutions[34].atoms[0] != 0 && !Term_Equal(&substitutions[34], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_42; }
        substitutions[34] = subtree;
        subtree = Term_ExtractSubterm(&term1, 2);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_42; }
        substitutions[31] = subtree;
        if (term2.atoms[0] != 43) { goto RULE_42; }
        subtree = Term_ExtractSubterm(&term2, 1);
        if ((substitutions[33].atoms[0] != 0 && !Term_Equal(&substitutions[33], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_42; }
        substitutions[33] = subtree;
        subtree = Term_ExtractSubterm(&term2, 2);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_42; }
        substitutions[31] = subtree;
        Term conclusion = {0};
        conclusion.atoms[0] = 43;
        conclusion.atoms[1] = 40;
        if (!Term_OverrideSubterm(&conclusion, 2, &substitutions[31])) { goto RULE_42; }
        if (!Term_OverrideSubterm(&conclusion, 3, &substitutions[34])) { goto RULE_42; }
        if (!Term_OverrideSubterm(&conclusion, 4, &substitutions[33])) { goto RULE_42; }
        Truth conclusionTruth = Truth_Union(truth1, truth2);
        NAL_DerivedEvent(RuleTableReduce(conclusion, false), conclusionOccurrence, conclusionTruth, conclusionStamp,
                         currentTime, parentPriority, conceptPriority, occurrenceTimeOffset, validation_concept,
                         validation_cid);
    }

    RULE_42:
    {
        if (!doublePremise) { goto RULE_43; }
        Term substitutions[27 + NUM_ELEMENTS(Narsese_RuleTableVars)] = {0};
        Term subtree = {0};
        if (term1.atoms[0] != 43) { goto RULE_43; }
        subtree = Term_ExtractSubterm(&term1, 1);
        if ((substitutions[33].atoms[0] != 0 && !Term_Equal(&substitutions[33], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_43; }
        substitutions[33] = subtree;
        subtree = Term_ExtractSubterm(&term1, 2);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_43; }
        substitutions[31] = subtree;
        if (term2.atoms[0] != 43) { goto RULE_43; }
        subtree = Term_ExtractSubterm(&term2, 1);
        if ((substitutions[34].atoms[0] != 0 && !Term_Equal(&substitutions[34], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_43; }
        substitutions[34] = subtree;
        subtree = Term_ExtractSubterm(&term2, 2);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_43; }
        substitutions[31] = subtree;
        Term conclusion = {0};
        conclusion.atoms[0] = 43;
        conclusion.atoms[1] = 40;
        if (!Term_OverrideSubterm(&conclusion, 2, &substitutions[31])) { goto RULE_43; }
        if (!Term_OverrideSubterm(&conclusion, 3, &substitutions[34])) { goto RULE_43; }
        if (!Term_OverrideSubterm(&conclusion, 4, &substitutions[33])) { goto RULE_43; }
        Truth conclusionTruth = Truth_Union(truth2, truth1);
        NAL_DerivedEvent(RuleTableReduce(conclusion, false), conclusionOccurrence, conclusionTruth, conclusionStamp,
                         currentTime, parentPriority, conceptPriority, occurrenceTimeOffset, validation_concept,
                         validation_cid);
    }

    RULE_43:
    {
        if (!doublePremise) { goto RULE_44; }
        Term substitutions[27 + NUM_ELEMENTS(Narsese_RuleTableVars)] = {0};
        Term subtree = {0};
        if (term1.atoms[0] != 43) { goto RULE_44; }
        subtree = Term_ExtractSubterm(&term1, 1);
        if ((substitutions[34].atoms[0] != 0 && !Term_Equal(&substitutions[34], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_44; }
        substitutions[34] = subtree;
        subtree = Term_ExtractSubterm(&term1, 2);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_44; }
        substitutions[31] = subtree;
        if (term2.atoms[0] != 43) { goto RULE_44; }
        subtree = Term_ExtractSubterm(&term2, 1);
        if ((substitutions[33].atoms[0] != 0 && !Term_Equal(&substitutions[33], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_44; }
        substitutions[33] = subtree;
        subtree = Term_ExtractSubterm(&term2, 2);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_44; }
        substitutions[31] = subtree;
        Term conclusion = {0};
        conclusion.atoms[0] = 43;
        conclusion.atoms[1] = 54;
        if (!Term_OverrideSubterm(&conclusion, 2, &substitutions[31])) { goto RULE_44; }
        if (!Term_OverrideSubterm(&conclusion, 3, &substitutions[34])) { goto RULE_44; }
        if (!Term_OverrideSubterm(&conclusion, 4, &substitutions[33])) { goto RULE_44; }
        Truth conclusionTruth = Truth_Difference(truth1, truth2);
        NAL_DerivedEvent(RuleTableReduce(conclusion, false), conclusionOccurrence, conclusionTruth, conclusionStamp,
                         currentTime, parentPriority, conceptPriority, occurrenceTimeOffset, validation_concept,
                         validation_cid);
    }

    RULE_44:
    {
        if (!doublePremise) { goto RULE_45; }
        Term substitutions[27 + NUM_ELEMENTS(Narsese_RuleTableVars)] = {0};
        Term subtree = {0};
        if (term1.atoms[0] != 43) { goto RULE_45; }
        subtree = Term_ExtractSubterm(&term1, 1);
        if ((substitutions[33].atoms[0] != 0 && !Term_Equal(&substitutions[33], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_45; }
        substitutions[33] = subtree;
        subtree = Term_ExtractSubterm(&term1, 2);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_45; }
        substitutions[31] = subtree;
        if (term2.atoms[0] != 43) { goto RULE_45; }
        subtree = Term_ExtractSubterm(&term2, 1);
        if ((substitutions[34].atoms[0] != 0 && !Term_Equal(&substitutions[34], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_45; }
        substitutions[34] = subtree;
        subtree = Term_ExtractSubterm(&term2, 2);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_45; }
        substitutions[31] = subtree;
        Term conclusion = {0};
        conclusion.atoms[0] = 43;
        conclusion.atoms[1] = 54;
        if (!Term_OverrideSubterm(&conclusion, 2, &substitutions[31])) { goto RULE_45; }
        if (!Term_OverrideSubterm(&conclusion, 3, &substitutions[34])) { goto RULE_45; }
        if (!Term_OverrideSubterm(&conclusion, 4, &substitutions[33])) { goto RULE_45; }
        Truth conclusionTruth = Truth_Difference(truth2, truth1);
        NAL_DerivedEvent(RuleTableReduce(conclusion, false), conclusionOccurrence, conclusionTruth, conclusionStamp,
                         currentTime, parentPriority, conceptPriority, occurrenceTimeOffset, validation_concept,
                         validation_cid);
    }

    RULE_45:
    {
        if (!doublePremise) { goto RULE_46; }
        Term substitutions[27 + NUM_ELEMENTS(Narsese_RuleTableVars)] = {0};
        Term subtree = {0};
        if (term1.atoms[0] != 43) { goto RULE_46; }
        subtree = Term_ExtractSubterm(&term1, 1);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_46; }
        substitutions[31] = subtree;
        subtree = Term_ExtractSubterm(&term1, 2);
        if ((substitutions[34].atoms[0] != 0 && !Term_Equal(&substitutions[34], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_46; }
        substitutions[34] = subtree;
        if (term2.atoms[0] != 43) { goto RULE_46; }
        subtree = Term_ExtractSubterm(&term2, 1);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_46; }
        substitutions[31] = subtree;
        subtree = Term_ExtractSubterm(&term2, 2);
        if ((substitutions[33].atoms[0] != 0 && !Term_Equal(&substitutions[33], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_46; }
        substitutions[33] = subtree;
        Term conclusion = {0};
        conclusion.atoms[0] = 43;
        if (!Term_OverrideSubterm(&conclusion, 1, &substitutions[31])) { goto RULE_46; }
        conclusion.atoms[2] = 40;
        if (!Term_OverrideSubterm(&conclusion, 5, &substitutions[34])) { goto RULE_46; }
        if (!Term_OverrideSubterm(&conclusion, 6, &substitutions[33])) { goto RULE_46; }
        Truth conclusionTruth = Truth_Intersection(truth1, truth2);
        NAL_DerivedEvent(RuleTableReduce(conclusion, false), conclusionOccurrence, conclusionTruth, conclusionStamp,
                         currentTime, parentPriority, conceptPriority, occurrenceTimeOffset, validation_concept,
                         validation_cid);
    }

    RULE_46:
    {
        if (!doublePremise) { goto RULE_47; }
        Term substitutions[27 + NUM_ELEMENTS(Narsese_RuleTableVars)] = {0};
        Term subtree = {0};
        if (term1.atoms[0] != 43) { goto RULE_47; }
        subtree = Term_ExtractSubterm(&term1, 1);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_47; }
        substitutions[31] = subtree;
        subtree = Term_ExtractSubterm(&term1, 2);
        if ((substitutions[33].atoms[0] != 0 && !Term_Equal(&substitutions[33], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_47; }
        substitutions[33] = subtree;
        if (term2.atoms[0] != 43) { goto RULE_47; }
        subtree = Term_ExtractSubterm(&term2, 1);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_47; }
        substitutions[31] = subtree;
        subtree = Term_ExtractSubterm(&term2, 2);
        if ((substitutions[34].atoms[0] != 0 && !Term_Equal(&substitutions[34], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_47; }
        substitutions[34] = subtree;
        Term conclusion = {0};
        conclusion.atoms[0] = 43;
        if (!Term_OverrideSubterm(&conclusion, 1, &substitutions[31])) { goto RULE_47; }
        conclusion.atoms[2] = 40;
        if (!Term_OverrideSubterm(&conclusion, 5, &substitutions[34])) { goto RULE_47; }
        if (!Term_OverrideSubterm(&conclusion, 6, &substitutions[33])) { goto RULE_47; }
        Truth conclusionTruth = Truth_Intersection(truth2, truth1);
        NAL_DerivedEvent(RuleTableReduce(conclusion, false), conclusionOccurrence, conclusionTruth, conclusionStamp,
                         currentTime, parentPriority, conceptPriority, occurrenceTimeOffset, validation_concept,
                         validation_cid);
    }

    RULE_47:
    {
        if (!doublePremise) { goto RULE_48; }
        Term substitutions[27 + NUM_ELEMENTS(Narsese_RuleTableVars)] = {0};
        Term subtree = {0};
        if (term1.atoms[0] != 43) { goto RULE_48; }
        subtree = Term_ExtractSubterm(&term1, 1);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_48; }
        substitutions[31] = subtree;
        subtree = Term_ExtractSubterm(&term1, 2);
        if ((substitutions[34].atoms[0] != 0 && !Term_Equal(&substitutions[34], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_48; }
        substitutions[34] = subtree;
        if (term2.atoms[0] != 43) { goto RULE_48; }
        subtree = Term_ExtractSubterm(&term2, 1);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_48; }
        substitutions[31] = subtree;
        subtree = Term_ExtractSubterm(&term2, 2);
        if ((substitutions[33].atoms[0] != 0 && !Term_Equal(&substitutions[33], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_48; }
        substitutions[33] = subtree;
        Term conclusion = {0};
        conclusion.atoms[0] = 43;
        if (!Term_OverrideSubterm(&conclusion, 1, &substitutions[31])) { goto RULE_48; }
        conclusion.atoms[2] = 41;
        if (!Term_OverrideSubterm(&conclusion, 5, &substitutions[34])) { goto RULE_48; }
        if (!Term_OverrideSubterm(&conclusion, 6, &substitutions[33])) { goto RULE_48; }
        Truth conclusionTruth = Truth_Union(truth1, truth2);
        NAL_DerivedEvent(RuleTableReduce(conclusion, false), conclusionOccurrence, conclusionTruth, conclusionStamp,
                         currentTime, parentPriority, conceptPriority, occurrenceTimeOffset, validation_concept,
                         validation_cid);
    }

    RULE_48:
    {
        if (!doublePremise) { goto RULE_49; }
        Term substitutions[27 + NUM_ELEMENTS(Narsese_RuleTableVars)] = {0};
        Term subtree = {0};
        if (term1.atoms[0] != 43) { goto RULE_49; }
        subtree = Term_ExtractSubterm(&term1, 1);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_49; }
        substitutions[31] = subtree;
        subtree = Term_ExtractSubterm(&term1, 2);
        if ((substitutions[33].atoms[0] != 0 && !Term_Equal(&substitutions[33], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_49; }
        substitutions[33] = subtree;
        if (term2.atoms[0] != 43) { goto RULE_49; }
        subtree = Term_ExtractSubterm(&term2, 1);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_49; }
        substitutions[31] = subtree;
        subtree = Term_ExtractSubterm(&term2, 2);
        if ((substitutions[34].atoms[0] != 0 && !Term_Equal(&substitutions[34], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_49; }
        substitutions[34] = subtree;
        Term conclusion = {0};
        conclusion.atoms[0] = 43;
        if (!Term_OverrideSubterm(&conclusion, 1, &substitutions[31])) { goto RULE_49; }
        conclusion.atoms[2] = 41;
        if (!Term_OverrideSubterm(&conclusion, 5, &substitutions[34])) { goto RULE_49; }
        if (!Term_OverrideSubterm(&conclusion, 6, &substitutions[33])) { goto RULE_49; }
        Truth conclusionTruth = Truth_Union(truth2, truth1);
        NAL_DerivedEvent(RuleTableReduce(conclusion, false), conclusionOccurrence, conclusionTruth, conclusionStamp,
                         currentTime, parentPriority, conceptPriority, occurrenceTimeOffset, validation_concept,
                         validation_cid);
    }

    RULE_49:
    {
        if (!doublePremise) { goto RULE_50; }
        Term substitutions[27 + NUM_ELEMENTS(Narsese_RuleTableVars)] = {0};
        Term subtree = {0};
        if (term1.atoms[0] != 43) { goto RULE_50; }
        subtree = Term_ExtractSubterm(&term1, 1);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_50; }
        substitutions[31] = subtree;
        subtree = Term_ExtractSubterm(&term1, 2);
        if ((substitutions[34].atoms[0] != 0 && !Term_Equal(&substitutions[34], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_50; }
        substitutions[34] = subtree;
        if (term2.atoms[0] != 43) { goto RULE_50; }
        subtree = Term_ExtractSubterm(&term2, 1);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_50; }
        substitutions[31] = subtree;
        subtree = Term_ExtractSubterm(&term2, 2);
        if ((substitutions[33].atoms[0] != 0 && !Term_Equal(&substitutions[33], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_50; }
        substitutions[33] = subtree;
        Term conclusion = {0};
        conclusion.atoms[0] = 43;
        if (!Term_OverrideSubterm(&conclusion, 1, &substitutions[31])) { goto RULE_50; }
        conclusion.atoms[2] = 51;
        if (!Term_OverrideSubterm(&conclusion, 5, &substitutions[34])) { goto RULE_50; }
        if (!Term_OverrideSubterm(&conclusion, 6, &substitutions[33])) { goto RULE_50; }
        Truth conclusionTruth = Truth_Difference(truth1, truth2);
        NAL_DerivedEvent(RuleTableReduce(conclusion, false), conclusionOccurrence, conclusionTruth, conclusionStamp,
                         currentTime, parentPriority, conceptPriority, occurrenceTimeOffset, validation_concept,
                         validation_cid);
    }

    RULE_50:
    {
        if (!doublePremise) { goto RULE_51; }
        Term substitutions[27 + NUM_ELEMENTS(Narsese_RuleTableVars)] = {0};
        Term subtree = {0};
        if (term1.atoms[0] != 43) { goto RULE_51; }
        subtree = Term_ExtractSubterm(&term1, 1);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_51; }
        substitutions[31] = subtree;
        subtree = Term_ExtractSubterm(&term1, 2);
        if ((substitutions[33].atoms[0] != 0 && !Term_Equal(&substitutions[33], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_51; }
        substitutions[33] = subtree;
        if (term2.atoms[0] != 43) { goto RULE_51; }
        subtree = Term_ExtractSubterm(&term2, 1);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_51; }
        substitutions[31] = subtree;
        subtree = Term_ExtractSubterm(&term2, 2);
        if ((substitutions[34].atoms[0] != 0 && !Term_Equal(&substitutions[34], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_51; }
        substitutions[34] = subtree;
        Term conclusion = {0};
        conclusion.atoms[0] = 43;
        if (!Term_OverrideSubterm(&conclusion, 1, &substitutions[31])) { goto RULE_51; }
        conclusion.atoms[2] = 51;
        if (!Term_OverrideSubterm(&conclusion, 5, &substitutions[34])) { goto RULE_51; }
        if (!Term_OverrideSubterm(&conclusion, 6, &substitutions[33])) { goto RULE_51; }
        Truth conclusionTruth = Truth_Difference(truth2, truth1);
        NAL_DerivedEvent(RuleTableReduce(conclusion, false), conclusionOccurrence, conclusionTruth, conclusionStamp,
                         currentTime, parentPriority, conceptPriority, occurrenceTimeOffset, validation_concept,
                         validation_cid);
    }

    RULE_51:
    {
        if (!doublePremise) { goto RULE_52; }
        Term substitutions[27 + NUM_ELEMENTS(Narsese_RuleTableVars)] = {0};
        Term subtree = {0};
        if (term1.atoms[0] != 43) { goto RULE_52; }
        subtree = Term_ExtractSubterm(&term1, 1);
        if ((substitutions[33].atoms[0] != 0 && !Term_Equal(&substitutions[33], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_52; }
        substitutions[33] = subtree;
        subtree = Term_ExtractSubterm(&term1, 2);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_52; }
        substitutions[31] = subtree;
        if (term2.atoms[0] != 43) { goto RULE_52; }
        if (term2.atoms[1] != 41) { goto RULE_52; }
        subtree = Term_ExtractSubterm(&term2, 2);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_52; }
        substitutions[31] = subtree;
        subtree = Term_ExtractSubterm(&term2, 3);
        if ((substitutions[33].atoms[0] != 0 && !Term_Equal(&substitutions[33], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_52; }
        substitutions[33] = subtree;
        subtree = Term_ExtractSubterm(&term2, 4);
        if ((substitutions[34].atoms[0] != 0 && !Term_Equal(&substitutions[34], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_52; }
        substitutions[34] = subtree;
        Term conclusion = {0};
        conclusion.atoms[0] = 43;
        if (!Term_OverrideSubterm(&conclusion, 1, &substitutions[34])) { goto RULE_52; }
        if (!Term_OverrideSubterm(&conclusion, 2, &substitutions[31])) { goto RULE_52; }
        Truth conclusionTruth = Truth_DecomposePNN(truth1, truth2);
        NAL_DerivedEvent(RuleTableReduce(conclusion, false), conclusionOccurrence, conclusionTruth, conclusionStamp,
                         currentTime, parentPriority, conceptPriority, occurrenceTimeOffset, validation_concept,
                         validation_cid);
    }

    RULE_52:
    {
        if (!doublePremise) { goto RULE_53; }
        Term substitutions[27 + NUM_ELEMENTS(Narsese_RuleTableVars)] = {0};
        Term subtree = {0};
        if (term1.atoms[0] != 43) { goto RULE_53; }
        if (term1.atoms[1] != 41) { goto RULE_53; }
        subtree = Term_ExtractSubterm(&term1, 2);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_53; }
        substitutions[31] = subtree;
        subtree = Term_ExtractSubterm(&term1, 3);
        if ((substitutions[33].atoms[0] != 0 && !Term_Equal(&substitutions[33], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_53; }
        substitutions[33] = subtree;
        subtree = Term_ExtractSubterm(&term1, 4);
        if ((substitutions[34].atoms[0] != 0 && !Term_Equal(&substitutions[34], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_53; }
        substitutions[34] = subtree;
        if (term2.atoms[0] != 43) { goto RULE_53; }
        subtree = Term_ExtractSubterm(&term2, 1);
        if ((substitutions[33].atoms[0] != 0 && !Term_Equal(&substitutions[33], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_53; }
        substitutions[33] = subtree;
        subtree = Term_ExtractSubterm(&term2, 2);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_53; }
        substitutions[31] = subtree;
        Term conclusion = {0};
        conclusion.atoms[0] = 43;
        if (!Term_OverrideSubterm(&conclusion, 1, &substitutions[34])) { goto RULE_53; }
        if (!Term_OverrideSubterm(&conclusion, 2, &substitutions[31])) { goto RULE_53; }
        Truth conclusionTruth = Truth_DecomposePNN(truth2, truth1);
        NAL_DerivedEvent(RuleTableReduce(conclusion, false), conclusionOccurrence, conclusionTruth, conclusionStamp,
                         currentTime, parentPriority, conceptPriority, occurrenceTimeOffset, validation_concept,
                         validation_cid);
    }

    RULE_53:
    {
        if (!doublePremise) { goto RULE_54; }
        Term substitutions[27 + NUM_ELEMENTS(Narsese_RuleTableVars)] = {0};
        Term subtree = {0};
        if (term1.atoms[0] != 43) { goto RULE_54; }
        subtree = Term_ExtractSubterm(&term1, 1);
        if ((substitutions[34].atoms[0] != 0 && !Term_Equal(&substitutions[34], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_54; }
        substitutions[34] = subtree;
        subtree = Term_ExtractSubterm(&term1, 2);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_54; }
        substitutions[31] = subtree;
        if (term2.atoms[0] != 43) { goto RULE_54; }
        if (term2.atoms[1] != 41) { goto RULE_54; }
        subtree = Term_ExtractSubterm(&term2, 2);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_54; }
        substitutions[31] = subtree;
        subtree = Term_ExtractSubterm(&term2, 3);
        if ((substitutions[33].atoms[0] != 0 && !Term_Equal(&substitutions[33], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_54; }
        substitutions[33] = subtree;
        subtree = Term_ExtractSubterm(&term2, 4);
        if ((substitutions[34].atoms[0] != 0 && !Term_Equal(&substitutions[34], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_54; }
        substitutions[34] = subtree;
        Term conclusion = {0};
        conclusion.atoms[0] = 43;
        if (!Term_OverrideSubterm(&conclusion, 1, &substitutions[33])) { goto RULE_54; }
        if (!Term_OverrideSubterm(&conclusion, 2, &substitutions[31])) { goto RULE_54; }
        Truth conclusionTruth = Truth_DecomposePNN(truth1, truth2);
        NAL_DerivedEvent(RuleTableReduce(conclusion, false), conclusionOccurrence, conclusionTruth, conclusionStamp,
                         currentTime, parentPriority, conceptPriority, occurrenceTimeOffset, validation_concept,
                         validation_cid);
    }

    RULE_54:
    {
        if (!doublePremise) { goto RULE_55; }
        Term substitutions[27 + NUM_ELEMENTS(Narsese_RuleTableVars)] = {0};
        Term subtree = {0};
        if (term1.atoms[0] != 43) { goto RULE_55; }
        if (term1.atoms[1] != 41) { goto RULE_55; }
        subtree = Term_ExtractSubterm(&term1, 2);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_55; }
        substitutions[31] = subtree;
        subtree = Term_ExtractSubterm(&term1, 3);
        if ((substitutions[33].atoms[0] != 0 && !Term_Equal(&substitutions[33], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_55; }
        substitutions[33] = subtree;
        subtree = Term_ExtractSubterm(&term1, 4);
        if ((substitutions[34].atoms[0] != 0 && !Term_Equal(&substitutions[34], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_55; }
        substitutions[34] = subtree;
        if (term2.atoms[0] != 43) { goto RULE_55; }
        subtree = Term_ExtractSubterm(&term2, 1);
        if ((substitutions[34].atoms[0] != 0 && !Term_Equal(&substitutions[34], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_55; }
        substitutions[34] = subtree;
        subtree = Term_ExtractSubterm(&term2, 2);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_55; }
        substitutions[31] = subtree;
        Term conclusion = {0};
        conclusion.atoms[0] = 43;
        if (!Term_OverrideSubterm(&conclusion, 1, &substitutions[33])) { goto RULE_55; }
        if (!Term_OverrideSubterm(&conclusion, 2, &substitutions[31])) { goto RULE_55; }
        Truth conclusionTruth = Truth_DecomposePNN(truth2, truth1);
        NAL_DerivedEvent(RuleTableReduce(conclusion, false), conclusionOccurrence, conclusionTruth, conclusionStamp,
                         currentTime, parentPriority, conceptPriority, occurrenceTimeOffset, validation_concept,
                         validation_cid);
    }

    RULE_55:
    {
        if (!doublePremise) { goto RULE_56; }
        Term substitutions[27 + NUM_ELEMENTS(Narsese_RuleTableVars)] = {0};
        Term subtree = {0};
        if (term1.atoms[0] != 43) { goto RULE_56; }
        subtree = Term_ExtractSubterm(&term1, 1);
        if ((substitutions[33].atoms[0] != 0 && !Term_Equal(&substitutions[33], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_56; }
        substitutions[33] = subtree;
        subtree = Term_ExtractSubterm(&term1, 2);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_56; }
        substitutions[31] = subtree;
        if (term2.atoms[0] != 43) { goto RULE_56; }
        if (term2.atoms[1] != 40) { goto RULE_56; }
        subtree = Term_ExtractSubterm(&term2, 2);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_56; }
        substitutions[31] = subtree;
        subtree = Term_ExtractSubterm(&term2, 3);
        if ((substitutions[33].atoms[0] != 0 && !Term_Equal(&substitutions[33], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_56; }
        substitutions[33] = subtree;
        subtree = Term_ExtractSubterm(&term2, 4);
        if ((substitutions[34].atoms[0] != 0 && !Term_Equal(&substitutions[34], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_56; }
        substitutions[34] = subtree;
        Term conclusion = {0};
        conclusion.atoms[0] = 43;
        if (!Term_OverrideSubterm(&conclusion, 1, &substitutions[34])) { goto RULE_56; }
        if (!Term_OverrideSubterm(&conclusion, 2, &substitutions[31])) { goto RULE_56; }
        Truth conclusionTruth = Truth_DecomposeNPP(truth1, truth2);
        NAL_DerivedEvent(RuleTableReduce(conclusion, false), conclusionOccurrence, conclusionTruth, conclusionStamp,
                         currentTime, parentPriority, conceptPriority, occurrenceTimeOffset, validation_concept,
                         validation_cid);
    }

    RULE_56:
    {
        if (!doublePremise) { goto RULE_57; }
        Term substitutions[27 + NUM_ELEMENTS(Narsese_RuleTableVars)] = {0};
        Term subtree = {0};
        if (term1.atoms[0] != 43) { goto RULE_57; }
        if (term1.atoms[1] != 40) { goto RULE_57; }
        subtree = Term_ExtractSubterm(&term1, 2);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_57; }
        substitutions[31] = subtree;
        subtree = Term_ExtractSubterm(&term1, 3);
        if ((substitutions[33].atoms[0] != 0 && !Term_Equal(&substitutions[33], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_57; }
        substitutions[33] = subtree;
        subtree = Term_ExtractSubterm(&term1, 4);
        if ((substitutions[34].atoms[0] != 0 && !Term_Equal(&substitutions[34], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_57; }
        substitutions[34] = subtree;
        if (term2.atoms[0] != 43) { goto RULE_57; }
        subtree = Term_ExtractSubterm(&term2, 1);
        if ((substitutions[33].atoms[0] != 0 && !Term_Equal(&substitutions[33], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_57; }
        substitutions[33] = subtree;
        subtree = Term_ExtractSubterm(&term2, 2);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_57; }
        substitutions[31] = subtree;
        Term conclusion = {0};
        conclusion.atoms[0] = 43;
        if (!Term_OverrideSubterm(&conclusion, 1, &substitutions[34])) { goto RULE_57; }
        if (!Term_OverrideSubterm(&conclusion, 2, &substitutions[31])) { goto RULE_57; }
        Truth conclusionTruth = Truth_DecomposeNPP(truth2, truth1);
        NAL_DerivedEvent(RuleTableReduce(conclusion, false), conclusionOccurrence, conclusionTruth, conclusionStamp,
                         currentTime, parentPriority, conceptPriority, occurrenceTimeOffset, validation_concept,
                         validation_cid);
    }

    RULE_57:
    {
        if (!doublePremise) { goto RULE_58; }
        Term substitutions[27 + NUM_ELEMENTS(Narsese_RuleTableVars)] = {0};
        Term subtree = {0};
        if (term1.atoms[0] != 43) { goto RULE_58; }
        subtree = Term_ExtractSubterm(&term1, 1);
        if ((substitutions[34].atoms[0] != 0 && !Term_Equal(&substitutions[34], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_58; }
        substitutions[34] = subtree;
        subtree = Term_ExtractSubterm(&term1, 2);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_58; }
        substitutions[31] = subtree;
        if (term2.atoms[0] != 43) { goto RULE_58; }
        if (term2.atoms[1] != 40) { goto RULE_58; }
        subtree = Term_ExtractSubterm(&term2, 2);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_58; }
        substitutions[31] = subtree;
        subtree = Term_ExtractSubterm(&term2, 3);
        if ((substitutions[33].atoms[0] != 0 && !Term_Equal(&substitutions[33], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_58; }
        substitutions[33] = subtree;
        subtree = Term_ExtractSubterm(&term2, 4);
        if ((substitutions[34].atoms[0] != 0 && !Term_Equal(&substitutions[34], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_58; }
        substitutions[34] = subtree;
        Term conclusion = {0};
        conclusion.atoms[0] = 43;
        if (!Term_OverrideSubterm(&conclusion, 1, &substitutions[33])) { goto RULE_58; }
        if (!Term_OverrideSubterm(&conclusion, 2, &substitutions[31])) { goto RULE_58; }
        Truth conclusionTruth = Truth_DecomposeNPP(truth1, truth2);
        NAL_DerivedEvent(RuleTableReduce(conclusion, false), conclusionOccurrence, conclusionTruth, conclusionStamp,
                         currentTime, parentPriority, conceptPriority, occurrenceTimeOffset, validation_concept,
                         validation_cid);
    }

    RULE_58:
    {
        if (!doublePremise) { goto RULE_59; }
        Term substitutions[27 + NUM_ELEMENTS(Narsese_RuleTableVars)] = {0};
        Term subtree = {0};
        if (term1.atoms[0] != 43) { goto RULE_59; }
        if (term1.atoms[1] != 40) { goto RULE_59; }
        subtree = Term_ExtractSubterm(&term1, 2);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_59; }
        substitutions[31] = subtree;
        subtree = Term_ExtractSubterm(&term1, 3);
        if ((substitutions[33].atoms[0] != 0 && !Term_Equal(&substitutions[33], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_59; }
        substitutions[33] = subtree;
        subtree = Term_ExtractSubterm(&term1, 4);
        if ((substitutions[34].atoms[0] != 0 && !Term_Equal(&substitutions[34], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_59; }
        substitutions[34] = subtree;
        if (term2.atoms[0] != 43) { goto RULE_59; }
        subtree = Term_ExtractSubterm(&term2, 1);
        if ((substitutions[34].atoms[0] != 0 && !Term_Equal(&substitutions[34], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_59; }
        substitutions[34] = subtree;
        subtree = Term_ExtractSubterm(&term2, 2);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_59; }
        substitutions[31] = subtree;
        Term conclusion = {0};
        conclusion.atoms[0] = 43;
        if (!Term_OverrideSubterm(&conclusion, 1, &substitutions[33])) { goto RULE_59; }
        if (!Term_OverrideSubterm(&conclusion, 2, &substitutions[31])) { goto RULE_59; }
        Truth conclusionTruth = Truth_DecomposeNPP(truth2, truth1);
        NAL_DerivedEvent(RuleTableReduce(conclusion, false), conclusionOccurrence, conclusionTruth, conclusionStamp,
                         currentTime, parentPriority, conceptPriority, occurrenceTimeOffset, validation_concept,
                         validation_cid);
    }

    RULE_59:
    {
        if (!doublePremise) { goto RULE_60; }
        Term substitutions[27 + NUM_ELEMENTS(Narsese_RuleTableVars)] = {0};
        Term subtree = {0};
        if (term1.atoms[0] != 43) { goto RULE_60; }
        subtree = Term_ExtractSubterm(&term1, 1);
        if ((substitutions[33].atoms[0] != 0 && !Term_Equal(&substitutions[33], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_60; }
        substitutions[33] = subtree;
        subtree = Term_ExtractSubterm(&term1, 2);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_60; }
        substitutions[31] = subtree;
        if (term2.atoms[0] != 43) { goto RULE_60; }
        if (term2.atoms[1] != 54) { goto RULE_60; }
        subtree = Term_ExtractSubterm(&term2, 2);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_60; }
        substitutions[31] = subtree;
        subtree = Term_ExtractSubterm(&term2, 3);
        if ((substitutions[33].atoms[0] != 0 && !Term_Equal(&substitutions[33], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_60; }
        substitutions[33] = subtree;
        subtree = Term_ExtractSubterm(&term2, 4);
        if ((substitutions[34].atoms[0] != 0 && !Term_Equal(&substitutions[34], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_60; }
        substitutions[34] = subtree;
        Term conclusion = {0};
        conclusion.atoms[0] = 43;
        if (!Term_OverrideSubterm(&conclusion, 1, &substitutions[34])) { goto RULE_60; }
        if (!Term_OverrideSubterm(&conclusion, 2, &substitutions[31])) { goto RULE_60; }
        Truth conclusionTruth = Truth_DecomposePNP(truth1, truth2);
        NAL_DerivedEvent(RuleTableReduce(conclusion, false), conclusionOccurrence, conclusionTruth, conclusionStamp,
                         currentTime, parentPriority, conceptPriority, occurrenceTimeOffset, validation_concept,
                         validation_cid);
    }

    RULE_60:
    {
        if (!doublePremise) { goto RULE_61; }
        Term substitutions[27 + NUM_ELEMENTS(Narsese_RuleTableVars)] = {0};
        Term subtree = {0};
        if (term1.atoms[0] != 43) { goto RULE_61; }
        if (term1.atoms[1] != 54) { goto RULE_61; }
        subtree = Term_ExtractSubterm(&term1, 2);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_61; }
        substitutions[31] = subtree;
        subtree = Term_ExtractSubterm(&term1, 3);
        if ((substitutions[33].atoms[0] != 0 && !Term_Equal(&substitutions[33], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_61; }
        substitutions[33] = subtree;
        subtree = Term_ExtractSubterm(&term1, 4);
        if ((substitutions[34].atoms[0] != 0 && !Term_Equal(&substitutions[34], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_61; }
        substitutions[34] = subtree;
        if (term2.atoms[0] != 43) { goto RULE_61; }
        subtree = Term_ExtractSubterm(&term2, 1);
        if ((substitutions[33].atoms[0] != 0 && !Term_Equal(&substitutions[33], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_61; }
        substitutions[33] = subtree;
        subtree = Term_ExtractSubterm(&term2, 2);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_61; }
        substitutions[31] = subtree;
        Term conclusion = {0};
        conclusion.atoms[0] = 43;
        if (!Term_OverrideSubterm(&conclusion, 1, &substitutions[34])) { goto RULE_61; }
        if (!Term_OverrideSubterm(&conclusion, 2, &substitutions[31])) { goto RULE_61; }
        Truth conclusionTruth = Truth_DecomposePNP(truth2, truth1);
        NAL_DerivedEvent(RuleTableReduce(conclusion, false), conclusionOccurrence, conclusionTruth, conclusionStamp,
                         currentTime, parentPriority, conceptPriority, occurrenceTimeOffset, validation_concept,
                         validation_cid);
    }

    RULE_61:
    {
        if (!doublePremise) { goto RULE_62; }
        Term substitutions[27 + NUM_ELEMENTS(Narsese_RuleTableVars)] = {0};
        Term subtree = {0};
        if (term1.atoms[0] != 43) { goto RULE_62; }
        subtree = Term_ExtractSubterm(&term1, 1);
        if ((substitutions[33].atoms[0] != 0 && !Term_Equal(&substitutions[33], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_62; }
        substitutions[33] = subtree;
        subtree = Term_ExtractSubterm(&term1, 2);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_62; }
        substitutions[31] = subtree;
        if (term2.atoms[0] != 43) { goto RULE_62; }
        if (term2.atoms[1] != 54) { goto RULE_62; }
        subtree = Term_ExtractSubterm(&term2, 2);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_62; }
        substitutions[31] = subtree;
        subtree = Term_ExtractSubterm(&term2, 3);
        if ((substitutions[34].atoms[0] != 0 && !Term_Equal(&substitutions[34], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_62; }
        substitutions[34] = subtree;
        subtree = Term_ExtractSubterm(&term2, 4);
        if ((substitutions[33].atoms[0] != 0 && !Term_Equal(&substitutions[33], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_62; }
        substitutions[33] = subtree;
        Term conclusion = {0};
        conclusion.atoms[0] = 43;
        if (!Term_OverrideSubterm(&conclusion, 1, &substitutions[34])) { goto RULE_62; }
        if (!Term_OverrideSubterm(&conclusion, 2, &substitutions[31])) { goto RULE_62; }
        Truth conclusionTruth = Truth_DecomposeNNN(truth1, truth2);
        NAL_DerivedEvent(RuleTableReduce(conclusion, false), conclusionOccurrence, conclusionTruth, conclusionStamp,
                         currentTime, parentPriority, conceptPriority, occurrenceTimeOffset, validation_concept,
                         validation_cid);
    }

    RULE_62:
    {
        if (!doublePremise) { goto RULE_63; }
        Term substitutions[27 + NUM_ELEMENTS(Narsese_RuleTableVars)] = {0};
        Term subtree = {0};
        if (term1.atoms[0] != 43) { goto RULE_63; }
        if (term1.atoms[1] != 54) { goto RULE_63; }
        subtree = Term_ExtractSubterm(&term1, 2);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_63; }
        substitutions[31] = subtree;
        subtree = Term_ExtractSubterm(&term1, 3);
        if ((substitutions[34].atoms[0] != 0 && !Term_Equal(&substitutions[34], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_63; }
        substitutions[34] = subtree;
        subtree = Term_ExtractSubterm(&term1, 4);
        if ((substitutions[33].atoms[0] != 0 && !Term_Equal(&substitutions[33], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_63; }
        substitutions[33] = subtree;
        if (term2.atoms[0] != 43) { goto RULE_63; }
        subtree = Term_ExtractSubterm(&term2, 1);
        if ((substitutions[33].atoms[0] != 0 && !Term_Equal(&substitutions[33], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_63; }
        substitutions[33] = subtree;
        subtree = Term_ExtractSubterm(&term2, 2);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_63; }
        substitutions[31] = subtree;
        Term conclusion = {0};
        conclusion.atoms[0] = 43;
        if (!Term_OverrideSubterm(&conclusion, 1, &substitutions[34])) { goto RULE_63; }
        if (!Term_OverrideSubterm(&conclusion, 2, &substitutions[31])) { goto RULE_63; }
        Truth conclusionTruth = Truth_DecomposeNNN(truth2, truth1);
        NAL_DerivedEvent(RuleTableReduce(conclusion, false), conclusionOccurrence, conclusionTruth, conclusionStamp,
                         currentTime, parentPriority, conceptPriority, occurrenceTimeOffset, validation_concept,
                         validation_cid);
    }

    RULE_63:
    {
        if (!doublePremise) { goto RULE_64; }
        Term substitutions[27 + NUM_ELEMENTS(Narsese_RuleTableVars)] = {0};
        Term subtree = {0};
        if (term1.atoms[0] != 43) { goto RULE_64; }
        subtree = Term_ExtractSubterm(&term1, 1);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_64; }
        substitutions[31] = subtree;
        subtree = Term_ExtractSubterm(&term1, 2);
        if ((substitutions[33].atoms[0] != 0 && !Term_Equal(&substitutions[33], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_64; }
        substitutions[33] = subtree;
        if (term2.atoms[0] != 43) { goto RULE_64; }
        subtree = Term_ExtractSubterm(&term2, 1);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_64; }
        substitutions[31] = subtree;
        if (term2.atoms[2] != 40) { goto RULE_64; }
        subtree = Term_ExtractSubterm(&term2, 5);
        if ((substitutions[33].atoms[0] != 0 && !Term_Equal(&substitutions[33], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_64; }
        substitutions[33] = subtree;
        subtree = Term_ExtractSubterm(&term2, 6);
        if ((substitutions[34].atoms[0] != 0 && !Term_Equal(&substitutions[34], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_64; }
        substitutions[34] = subtree;
        Term conclusion = {0};
        conclusion.atoms[0] = 43;
        if (!Term_OverrideSubterm(&conclusion, 1, &substitutions[31])) { goto RULE_64; }
        if (!Term_OverrideSubterm(&conclusion, 2, &substitutions[34])) { goto RULE_64; }
        Truth conclusionTruth = Truth_DecomposePNN(truth1, truth2);
        NAL_DerivedEvent(RuleTableReduce(conclusion, false), conclusionOccurrence, conclusionTruth, conclusionStamp,
                         currentTime, parentPriority, conceptPriority, occurrenceTimeOffset, validation_concept,
                         validation_cid);
    }

    RULE_64:
    {
        if (!doublePremise) { goto RULE_65; }
        Term substitutions[27 + NUM_ELEMENTS(Narsese_RuleTableVars)] = {0};
        Term subtree = {0};
        if (term1.atoms[0] != 43) { goto RULE_65; }
        subtree = Term_ExtractSubterm(&term1, 1);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_65; }
        substitutions[31] = subtree;
        if (term1.atoms[2] != 40) { goto RULE_65; }
        subtree = Term_ExtractSubterm(&term1, 5);
        if ((substitutions[33].atoms[0] != 0 && !Term_Equal(&substitutions[33], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_65; }
        substitutions[33] = subtree;
        subtree = Term_ExtractSubterm(&term1, 6);
        if ((substitutions[34].atoms[0] != 0 && !Term_Equal(&substitutions[34], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_65; }
        substitutions[34] = subtree;
        if (term2.atoms[0] != 43) { goto RULE_65; }
        subtree = Term_ExtractSubterm(&term2, 1);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_65; }
        substitutions[31] = subtree;
        subtree = Term_ExtractSubterm(&term2, 2);
        if ((substitutions[33].atoms[0] != 0 && !Term_Equal(&substitutions[33], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_65; }
        substitutions[33] = subtree;
        Term conclusion = {0};
        conclusion.atoms[0] = 43;
        if (!Term_OverrideSubterm(&conclusion, 1, &substitutions[31])) { goto RULE_65; }
        if (!Term_OverrideSubterm(&conclusion, 2, &substitutions[34])) { goto RULE_65; }
        Truth conclusionTruth = Truth_DecomposePNN(truth2, truth1);
        NAL_DerivedEvent(RuleTableReduce(conclusion, false), conclusionOccurrence, conclusionTruth, conclusionStamp,
                         currentTime, parentPriority, conceptPriority, occurrenceTimeOffset, validation_concept,
                         validation_cid);
    }

    RULE_65:
    {
        if (!doublePremise) { goto RULE_66; }
        Term substitutions[27 + NUM_ELEMENTS(Narsese_RuleTableVars)] = {0};
        Term subtree = {0};
        if (term1.atoms[0] != 43) { goto RULE_66; }
        subtree = Term_ExtractSubterm(&term1, 1);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_66; }
        substitutions[31] = subtree;
        subtree = Term_ExtractSubterm(&term1, 2);
        if ((substitutions[34].atoms[0] != 0 && !Term_Equal(&substitutions[34], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_66; }
        substitutions[34] = subtree;
        if (term2.atoms[0] != 43) { goto RULE_66; }
        subtree = Term_ExtractSubterm(&term2, 1);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_66; }
        substitutions[31] = subtree;
        if (term2.atoms[2] != 40) { goto RULE_66; }
        subtree = Term_ExtractSubterm(&term2, 5);
        if ((substitutions[33].atoms[0] != 0 && !Term_Equal(&substitutions[33], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_66; }
        substitutions[33] = subtree;
        subtree = Term_ExtractSubterm(&term2, 6);
        if ((substitutions[34].atoms[0] != 0 && !Term_Equal(&substitutions[34], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_66; }
        substitutions[34] = subtree;
        Term conclusion = {0};
        conclusion.atoms[0] = 43;
        if (!Term_OverrideSubterm(&conclusion, 1, &substitutions[31])) { goto RULE_66; }
        if (!Term_OverrideSubterm(&conclusion, 2, &substitutions[33])) { goto RULE_66; }
        Truth conclusionTruth = Truth_DecomposePNN(truth1, truth2);
        NAL_DerivedEvent(RuleTableReduce(conclusion, false), conclusionOccurrence, conclusionTruth, conclusionStamp,
                         currentTime, parentPriority, conceptPriority, occurrenceTimeOffset, validation_concept,
                         validation_cid);
    }

    RULE_66:
    {
        if (!doublePremise) { goto RULE_67; }
        Term substitutions[27 + NUM_ELEMENTS(Narsese_RuleTableVars)] = {0};
        Term subtree = {0};
        if (term1.atoms[0] != 43) { goto RULE_67; }
        subtree = Term_ExtractSubterm(&term1, 1);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_67; }
        substitutions[31] = subtree;
        if (term1.atoms[2] != 40) { goto RULE_67; }
        subtree = Term_ExtractSubterm(&term1, 5);
        if ((substitutions[33].atoms[0] != 0 && !Term_Equal(&substitutions[33], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_67; }
        substitutions[33] = subtree;
        subtree = Term_ExtractSubterm(&term1, 6);
        if ((substitutions[34].atoms[0] != 0 && !Term_Equal(&substitutions[34], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_67; }
        substitutions[34] = subtree;
        if (term2.atoms[0] != 43) { goto RULE_67; }
        subtree = Term_ExtractSubterm(&term2, 1);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_67; }
        substitutions[31] = subtree;
        subtree = Term_ExtractSubterm(&term2, 2);
        if ((substitutions[34].atoms[0] != 0 && !Term_Equal(&substitutions[34], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_67; }
        substitutions[34] = subtree;
        Term conclusion = {0};
        conclusion.atoms[0] = 43;
        if (!Term_OverrideSubterm(&conclusion, 1, &substitutions[31])) { goto RULE_67; }
        if (!Term_OverrideSubterm(&conclusion, 2, &substitutions[33])) { goto RULE_67; }
        Truth conclusionTruth = Truth_DecomposePNN(truth2, truth1);
        NAL_DerivedEvent(RuleTableReduce(conclusion, false), conclusionOccurrence, conclusionTruth, conclusionStamp,
                         currentTime, parentPriority, conceptPriority, occurrenceTimeOffset, validation_concept,
                         validation_cid);
    }

    RULE_67:
    {
        if (!doublePremise) { goto RULE_68; }
        Term substitutions[27 + NUM_ELEMENTS(Narsese_RuleTableVars)] = {0};
        Term subtree = {0};
        if (term1.atoms[0] != 43) { goto RULE_68; }
        subtree = Term_ExtractSubterm(&term1, 1);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_68; }
        substitutions[31] = subtree;
        subtree = Term_ExtractSubterm(&term1, 2);
        if ((substitutions[33].atoms[0] != 0 && !Term_Equal(&substitutions[33], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_68; }
        substitutions[33] = subtree;
        if (term2.atoms[0] != 43) { goto RULE_68; }
        subtree = Term_ExtractSubterm(&term2, 1);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_68; }
        substitutions[31] = subtree;
        if (term2.atoms[2] != 41) { goto RULE_68; }
        subtree = Term_ExtractSubterm(&term2, 5);
        if ((substitutions[33].atoms[0] != 0 && !Term_Equal(&substitutions[33], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_68; }
        substitutions[33] = subtree;
        subtree = Term_ExtractSubterm(&term2, 6);
        if ((substitutions[34].atoms[0] != 0 && !Term_Equal(&substitutions[34], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_68; }
        substitutions[34] = subtree;
        Term conclusion = {0};
        conclusion.atoms[0] = 43;
        if (!Term_OverrideSubterm(&conclusion, 1, &substitutions[31])) { goto RULE_68; }
        if (!Term_OverrideSubterm(&conclusion, 2, &substitutions[34])) { goto RULE_68; }
        Truth conclusionTruth = Truth_DecomposeNPP(truth1, truth2);
        NAL_DerivedEvent(RuleTableReduce(conclusion, false), conclusionOccurrence, conclusionTruth, conclusionStamp,
                         currentTime, parentPriority, conceptPriority, occurrenceTimeOffset, validation_concept,
                         validation_cid);
    }

    RULE_68:
    {
        if (!doublePremise) { goto RULE_69; }
        Term substitutions[27 + NUM_ELEMENTS(Narsese_RuleTableVars)] = {0};
        Term subtree = {0};
        if (term1.atoms[0] != 43) { goto RULE_69; }
        subtree = Term_ExtractSubterm(&term1, 1);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_69; }
        substitutions[31] = subtree;
        if (term1.atoms[2] != 41) { goto RULE_69; }
        subtree = Term_ExtractSubterm(&term1, 5);
        if ((substitutions[33].atoms[0] != 0 && !Term_Equal(&substitutions[33], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_69; }
        substitutions[33] = subtree;
        subtree = Term_ExtractSubterm(&term1, 6);
        if ((substitutions[34].atoms[0] != 0 && !Term_Equal(&substitutions[34], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_69; }
        substitutions[34] = subtree;
        if (term2.atoms[0] != 43) { goto RULE_69; }
        subtree = Term_ExtractSubterm(&term2, 1);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_69; }
        substitutions[31] = subtree;
        subtree = Term_ExtractSubterm(&term2, 2);
        if ((substitutions[33].atoms[0] != 0 && !Term_Equal(&substitutions[33], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_69; }
        substitutions[33] = subtree;
        Term conclusion = {0};
        conclusion.atoms[0] = 43;
        if (!Term_OverrideSubterm(&conclusion, 1, &substitutions[31])) { goto RULE_69; }
        if (!Term_OverrideSubterm(&conclusion, 2, &substitutions[34])) { goto RULE_69; }
        Truth conclusionTruth = Truth_DecomposeNPP(truth2, truth1);
        NAL_DerivedEvent(RuleTableReduce(conclusion, false), conclusionOccurrence, conclusionTruth, conclusionStamp,
                         currentTime, parentPriority, conceptPriority, occurrenceTimeOffset, validation_concept,
                         validation_cid);
    }

    RULE_69:
    {
        if (!doublePremise) { goto RULE_70; }
        Term substitutions[27 + NUM_ELEMENTS(Narsese_RuleTableVars)] = {0};
        Term subtree = {0};
        if (term1.atoms[0] != 43) { goto RULE_70; }
        subtree = Term_ExtractSubterm(&term1, 1);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_70; }
        substitutions[31] = subtree;
        subtree = Term_ExtractSubterm(&term1, 2);
        if ((substitutions[34].atoms[0] != 0 && !Term_Equal(&substitutions[34], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_70; }
        substitutions[34] = subtree;
        if (term2.atoms[0] != 43) { goto RULE_70; }
        subtree = Term_ExtractSubterm(&term2, 1);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_70; }
        substitutions[31] = subtree;
        if (term2.atoms[2] != 41) { goto RULE_70; }
        subtree = Term_ExtractSubterm(&term2, 5);
        if ((substitutions[33].atoms[0] != 0 && !Term_Equal(&substitutions[33], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_70; }
        substitutions[33] = subtree;
        subtree = Term_ExtractSubterm(&term2, 6);
        if ((substitutions[34].atoms[0] != 0 && !Term_Equal(&substitutions[34], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_70; }
        substitutions[34] = subtree;
        Term conclusion = {0};
        conclusion.atoms[0] = 43;
        if (!Term_OverrideSubterm(&conclusion, 1, &substitutions[31])) { goto RULE_70; }
        if (!Term_OverrideSubterm(&conclusion, 2, &substitutions[33])) { goto RULE_70; }
        Truth conclusionTruth = Truth_DecomposeNPP(truth1, truth2);
        NAL_DerivedEvent(RuleTableReduce(conclusion, false), conclusionOccurrence, conclusionTruth, conclusionStamp,
                         currentTime, parentPriority, conceptPriority, occurrenceTimeOffset, validation_concept,
                         validation_cid);
    }

    RULE_70:
    {
        if (!doublePremise) { goto RULE_71; }
        Term substitutions[27 + NUM_ELEMENTS(Narsese_RuleTableVars)] = {0};
        Term subtree = {0};
        if (term1.atoms[0] != 43) { goto RULE_71; }
        subtree = Term_ExtractSubterm(&term1, 1);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_71; }
        substitutions[31] = subtree;
        if (term1.atoms[2] != 41) { goto RULE_71; }
        subtree = Term_ExtractSubterm(&term1, 5);
        if ((substitutions[33].atoms[0] != 0 && !Term_Equal(&substitutions[33], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_71; }
        substitutions[33] = subtree;
        subtree = Term_ExtractSubterm(&term1, 6);
        if ((substitutions[34].atoms[0] != 0 && !Term_Equal(&substitutions[34], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_71; }
        substitutions[34] = subtree;
        if (term2.atoms[0] != 43) { goto RULE_71; }
        subtree = Term_ExtractSubterm(&term2, 1);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_71; }
        substitutions[31] = subtree;
        subtree = Term_ExtractSubterm(&term2, 2);
        if ((substitutions[34].atoms[0] != 0 && !Term_Equal(&substitutions[34], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_71; }
        substitutions[34] = subtree;
        Term conclusion = {0};
        conclusion.atoms[0] = 43;
        if (!Term_OverrideSubterm(&conclusion, 1, &substitutions[31])) { goto RULE_71; }
        if (!Term_OverrideSubterm(&conclusion, 2, &substitutions[33])) { goto RULE_71; }
        Truth conclusionTruth = Truth_DecomposeNPP(truth2, truth1);
        NAL_DerivedEvent(RuleTableReduce(conclusion, false), conclusionOccurrence, conclusionTruth, conclusionStamp,
                         currentTime, parentPriority, conceptPriority, occurrenceTimeOffset, validation_concept,
                         validation_cid);
    }

    RULE_71:
    {
        if (!doublePremise) { goto RULE_72; }
        Term substitutions[27 + NUM_ELEMENTS(Narsese_RuleTableVars)] = {0};
        Term subtree = {0};
        if (term1.atoms[0] != 43) { goto RULE_72; }
        subtree = Term_ExtractSubterm(&term1, 1);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_72; }
        substitutions[31] = subtree;
        subtree = Term_ExtractSubterm(&term1, 2);
        if ((substitutions[33].atoms[0] != 0 && !Term_Equal(&substitutions[33], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_72; }
        substitutions[33] = subtree;
        if (term2.atoms[0] != 43) { goto RULE_72; }
        subtree = Term_ExtractSubterm(&term2, 1);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_72; }
        substitutions[31] = subtree;
        if (term2.atoms[2] != 51) { goto RULE_72; }
        subtree = Term_ExtractSubterm(&term2, 5);
        if ((substitutions[33].atoms[0] != 0 && !Term_Equal(&substitutions[33], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_72; }
        substitutions[33] = subtree;
        subtree = Term_ExtractSubterm(&term2, 6);
        if ((substitutions[34].atoms[0] != 0 && !Term_Equal(&substitutions[34], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_72; }
        substitutions[34] = subtree;
        Term conclusion = {0};
        conclusion.atoms[0] = 43;
        if (!Term_OverrideSubterm(&conclusion, 1, &substitutions[31])) { goto RULE_72; }
        if (!Term_OverrideSubterm(&conclusion, 2, &substitutions[34])) { goto RULE_72; }
        Truth conclusionTruth = Truth_DecomposePNP(truth1, truth2);
        NAL_DerivedEvent(RuleTableReduce(conclusion, false), conclusionOccurrence, conclusionTruth, conclusionStamp,
                         currentTime, parentPriority, conceptPriority, occurrenceTimeOffset, validation_concept,
                         validation_cid);
    }

    RULE_72:
    {
        if (!doublePremise) { goto RULE_73; }
        Term substitutions[27 + NUM_ELEMENTS(Narsese_RuleTableVars)] = {0};
        Term subtree = {0};
        if (term1.atoms[0] != 43) { goto RULE_73; }
        subtree = Term_ExtractSubterm(&term1, 1);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_73; }
        substitutions[31] = subtree;
        if (term1.atoms[2] != 51) { goto RULE_73; }
        subtree = Term_ExtractSubterm(&term1, 5);
        if ((substitutions[33].atoms[0] != 0 && !Term_Equal(&substitutions[33], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_73; }
        substitutions[33] = subtree;
        subtree = Term_ExtractSubterm(&term1, 6);
        if ((substitutions[34].atoms[0] != 0 && !Term_Equal(&substitutions[34], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_73; }
        substitutions[34] = subtree;
        if (term2.atoms[0] != 43) { goto RULE_73; }
        subtree = Term_ExtractSubterm(&term2, 1);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_73; }
        substitutions[31] = subtree;
        subtree = Term_ExtractSubterm(&term2, 2);
        if ((substitutions[33].atoms[0] != 0 && !Term_Equal(&substitutions[33], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_73; }
        substitutions[33] = subtree;
        Term conclusion = {0};
        conclusion.atoms[0] = 43;
        if (!Term_OverrideSubterm(&conclusion, 1, &substitutions[31])) { goto RULE_73; }
        if (!Term_OverrideSubterm(&conclusion, 2, &substitutions[34])) { goto RULE_73; }
        Truth conclusionTruth = Truth_DecomposePNP(truth2, truth1);
        NAL_DerivedEvent(RuleTableReduce(conclusion, false), conclusionOccurrence, conclusionTruth, conclusionStamp,
                         currentTime, parentPriority, conceptPriority, occurrenceTimeOffset, validation_concept,
                         validation_cid);
    }

    RULE_73:
    {
        if (!doublePremise) { goto RULE_74; }
        Term substitutions[27 + NUM_ELEMENTS(Narsese_RuleTableVars)] = {0};
        Term subtree = {0};
        if (term1.atoms[0] != 43) { goto RULE_74; }
        subtree = Term_ExtractSubterm(&term1, 1);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_74; }
        substitutions[31] = subtree;
        subtree = Term_ExtractSubterm(&term1, 2);
        if ((substitutions[33].atoms[0] != 0 && !Term_Equal(&substitutions[33], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_74; }
        substitutions[33] = subtree;
        if (term2.atoms[0] != 43) { goto RULE_74; }
        subtree = Term_ExtractSubterm(&term2, 1);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_74; }
        substitutions[31] = subtree;
        if (term2.atoms[2] != 51) { goto RULE_74; }
        subtree = Term_ExtractSubterm(&term2, 5);
        if ((substitutions[34].atoms[0] != 0 && !Term_Equal(&substitutions[34], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_74; }
        substitutions[34] = subtree;
        subtree = Term_ExtractSubterm(&term2, 6);
        if ((substitutions[33].atoms[0] != 0 && !Term_Equal(&substitutions[33], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_74; }
        substitutions[33] = subtree;
        Term conclusion = {0};
        conclusion.atoms[0] = 43;
        if (!Term_OverrideSubterm(&conclusion, 1, &substitutions[31])) { goto RULE_74; }
        if (!Term_OverrideSubterm(&conclusion, 2, &substitutions[34])) { goto RULE_74; }
        Truth conclusionTruth = Truth_DecomposeNNN(truth1, truth2);
        NAL_DerivedEvent(RuleTableReduce(conclusion, false), conclusionOccurrence, conclusionTruth, conclusionStamp,
                         currentTime, parentPriority, conceptPriority, occurrenceTimeOffset, validation_concept,
                         validation_cid);
    }

    RULE_74:
    {
        if (!doublePremise) { goto RULE_75; }
        Term substitutions[27 + NUM_ELEMENTS(Narsese_RuleTableVars)] = {0};
        Term subtree = {0};
        if (term1.atoms[0] != 43) { goto RULE_75; }
        subtree = Term_ExtractSubterm(&term1, 1);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_75; }
        substitutions[31] = subtree;
        if (term1.atoms[2] != 51) { goto RULE_75; }
        subtree = Term_ExtractSubterm(&term1, 5);
        if ((substitutions[34].atoms[0] != 0 && !Term_Equal(&substitutions[34], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_75; }
        substitutions[34] = subtree;
        subtree = Term_ExtractSubterm(&term1, 6);
        if ((substitutions[33].atoms[0] != 0 && !Term_Equal(&substitutions[33], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_75; }
        substitutions[33] = subtree;
        if (term2.atoms[0] != 43) { goto RULE_75; }
        subtree = Term_ExtractSubterm(&term2, 1);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_75; }
        substitutions[31] = subtree;
        subtree = Term_ExtractSubterm(&term2, 2);
        if ((substitutions[33].atoms[0] != 0 && !Term_Equal(&substitutions[33], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_75; }
        substitutions[33] = subtree;
        Term conclusion = {0};
        conclusion.atoms[0] = 43;
        if (!Term_OverrideSubterm(&conclusion, 1, &substitutions[31])) { goto RULE_75; }
        if (!Term_OverrideSubterm(&conclusion, 2, &substitutions[34])) { goto RULE_75; }
        Truth conclusionTruth = Truth_DecomposeNNN(truth2, truth1);
        NAL_DerivedEvent(RuleTableReduce(conclusion, false), conclusionOccurrence, conclusionTruth, conclusionStamp,
                         currentTime, parentPriority, conceptPriority, occurrenceTimeOffset, validation_concept,
                         validation_cid);
    }

    RULE_75:
    {
        if (doublePremise) { goto RULE_76; }
        Term substitutions[27 + NUM_ELEMENTS(Narsese_RuleTableVars)] = {0};
        Term subtree = {0};
        if (term1.atoms[0] != 43) { goto RULE_76; }
        if (term1.atoms[1] != 39) { goto RULE_76; }
        subtree = Term_ExtractSubterm(&term1, 2);
        if ((substitutions[32].atoms[0] != 0 && !Term_Equal(&substitutions[32], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_76; }
        substitutions[32] = subtree;
        subtree = Term_ExtractSubterm(&term1, 3);
        if ((substitutions[28].atoms[0] != 0 && !Term_Equal(&substitutions[28], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_76; }
        substitutions[28] = subtree;
        subtree = Term_ExtractSubterm(&term1, 4);
        if ((substitutions[29].atoms[0] != 0 && !Term_Equal(&substitutions[29], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_76; }
        substitutions[29] = subtree;
        Term conclusion = {0};
        conclusion.atoms[0] = 43;
        if (!Term_OverrideSubterm(&conclusion, 1, &substitutions[28])) { goto RULE_76; }
        conclusion.atoms[2] = 48;
        if (!Term_OverrideSubterm(&conclusion, 5, &substitutions[32])) { goto RULE_76; }
        if (!Term_OverrideSubterm(&conclusion, 6, &substitutions[29])) { goto RULE_76; }
        Truth conclusionTruth = Truth_StructuralDeduction(truth1, truth2);
        NAL_DerivedEvent(RuleTableReduce(conclusion, false), conclusionOccurrence, conclusionTruth, conclusionStamp,
                         currentTime, parentPriority, conceptPriority, occurrenceTimeOffset, validation_concept,
                         validation_cid);
    }

    RULE_76:
    {
        if (doublePremise) { goto RULE_77; }
        Term substitutions[27 + NUM_ELEMENTS(Narsese_RuleTableVars)] = {0};
        Term subtree = {0};
        if (term1.atoms[0] != 43) { goto RULE_77; }
        subtree = Term_ExtractSubterm(&term1, 1);
        if ((substitutions[28].atoms[0] != 0 && !Term_Equal(&substitutions[28], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_77; }
        substitutions[28] = subtree;
        if (term1.atoms[2] != 48) { goto RULE_77; }
        subtree = Term_ExtractSubterm(&term1, 5);
        if ((substitutions[32].atoms[0] != 0 && !Term_Equal(&substitutions[32], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_77; }
        substitutions[32] = subtree;
        subtree = Term_ExtractSubterm(&term1, 6);
        if ((substitutions[29].atoms[0] != 0 && !Term_Equal(&substitutions[29], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_77; }
        substitutions[29] = subtree;
        Term conclusion = {0};
        conclusion.atoms[0] = 43;
        conclusion.atoms[1] = 39;
        if (!Term_OverrideSubterm(&conclusion, 2, &substitutions[32])) { goto RULE_77; }
        if (!Term_OverrideSubterm(&conclusion, 3, &substitutions[28])) { goto RULE_77; }
        if (!Term_OverrideSubterm(&conclusion, 4, &substitutions[29])) { goto RULE_77; }
        Truth conclusionTruth = Truth_StructuralDeduction(truth1, truth2);
        NAL_DerivedEvent(RuleTableReduce(conclusion, false), conclusionOccurrence, conclusionTruth, conclusionStamp,
                         currentTime, parentPriority, conceptPriority, occurrenceTimeOffset, validation_concept,
                         validation_cid);
    }

    RULE_77:
    {
        if (doublePremise) { goto RULE_78; }
        Term substitutions[27 + NUM_ELEMENTS(Narsese_RuleTableVars)] = {0};
        Term subtree = {0};
        if (term1.atoms[0] != 43) { goto RULE_78; }
        if (term1.atoms[1] != 39) { goto RULE_78; }
        subtree = Term_ExtractSubterm(&term1, 2);
        if ((substitutions[32].atoms[0] != 0 && !Term_Equal(&substitutions[32], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_78; }
        substitutions[32] = subtree;
        subtree = Term_ExtractSubterm(&term1, 3);
        if ((substitutions[28].atoms[0] != 0 && !Term_Equal(&substitutions[28], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_78; }
        substitutions[28] = subtree;
        subtree = Term_ExtractSubterm(&term1, 4);
        if ((substitutions[29].atoms[0] != 0 && !Term_Equal(&substitutions[29], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_78; }
        substitutions[29] = subtree;
        Term conclusion = {0};
        conclusion.atoms[0] = 43;
        if (!Term_OverrideSubterm(&conclusion, 1, &substitutions[29])) { goto RULE_78; }
        conclusion.atoms[2] = 52;
        if (!Term_OverrideSubterm(&conclusion, 5, &substitutions[32])) { goto RULE_78; }
        if (!Term_OverrideSubterm(&conclusion, 6, &substitutions[28])) { goto RULE_78; }
        Truth conclusionTruth = Truth_StructuralDeduction(truth1, truth2);
        NAL_DerivedEvent(RuleTableReduce(conclusion, false), conclusionOccurrence, conclusionTruth, conclusionStamp,
                         currentTime, parentPriority, conceptPriority, occurrenceTimeOffset, validation_concept,
                         validation_cid);
    }

    RULE_78:
    {
        if (doublePremise) { goto RULE_79; }
        Term substitutions[27 + NUM_ELEMENTS(Narsese_RuleTableVars)] = {0};
        Term subtree = {0};
        if (term1.atoms[0] != 43) { goto RULE_79; }
        subtree = Term_ExtractSubterm(&term1, 1);
        if ((substitutions[29].atoms[0] != 0 && !Term_Equal(&substitutions[29], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_79; }
        substitutions[29] = subtree;
        if (term1.atoms[2] != 52) { goto RULE_79; }
        subtree = Term_ExtractSubterm(&term1, 5);
        if ((substitutions[32].atoms[0] != 0 && !Term_Equal(&substitutions[32], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_79; }
        substitutions[32] = subtree;
        subtree = Term_ExtractSubterm(&term1, 6);
        if ((substitutions[28].atoms[0] != 0 && !Term_Equal(&substitutions[28], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_79; }
        substitutions[28] = subtree;
        Term conclusion = {0};
        conclusion.atoms[0] = 43;
        conclusion.atoms[1] = 39;
        if (!Term_OverrideSubterm(&conclusion, 2, &substitutions[32])) { goto RULE_79; }
        if (!Term_OverrideSubterm(&conclusion, 3, &substitutions[28])) { goto RULE_79; }
        if (!Term_OverrideSubterm(&conclusion, 4, &substitutions[29])) { goto RULE_79; }
        Truth conclusionTruth = Truth_StructuralDeduction(truth1, truth2);
        NAL_DerivedEvent(RuleTableReduce(conclusion, false), conclusionOccurrence, conclusionTruth, conclusionStamp,
                         currentTime, parentPriority, conceptPriority, occurrenceTimeOffset, validation_concept,
                         validation_cid);
    }

    RULE_79:
    {
        if (doublePremise) { goto RULE_80; }
        Term substitutions[27 + NUM_ELEMENTS(Narsese_RuleTableVars)] = {0};
        Term subtree = {0};
        if (term1.atoms[0] != 43) { goto RULE_80; }
        subtree = Term_ExtractSubterm(&term1, 1);
        if ((substitutions[32].atoms[0] != 0 && !Term_Equal(&substitutions[32], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_80; }
        substitutions[32] = subtree;
        if (term1.atoms[2] != 39) { goto RULE_80; }
        subtree = Term_ExtractSubterm(&term1, 5);
        if ((substitutions[28].atoms[0] != 0 && !Term_Equal(&substitutions[28], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_80; }
        substitutions[28] = subtree;
        subtree = Term_ExtractSubterm(&term1, 6);
        if ((substitutions[29].atoms[0] != 0 && !Term_Equal(&substitutions[29], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_80; }
        substitutions[29] = subtree;
        Term conclusion = {0};
        conclusion.atoms[0] = 43;
        conclusion.atoms[1] = 49;
        if (!Term_OverrideSubterm(&conclusion, 2, &substitutions[28])) { goto RULE_80; }
        if (!Term_OverrideSubterm(&conclusion, 3, &substitutions[32])) { goto RULE_80; }
        if (!Term_OverrideSubterm(&conclusion, 4, &substitutions[29])) { goto RULE_80; }
        Truth conclusionTruth = Truth_StructuralDeduction(truth1, truth2);
        NAL_DerivedEvent(RuleTableReduce(conclusion, false), conclusionOccurrence, conclusionTruth, conclusionStamp,
                         currentTime, parentPriority, conceptPriority, occurrenceTimeOffset, validation_concept,
                         validation_cid);
    }

    RULE_80:
    {
        if (doublePremise) { goto RULE_81; }
        Term substitutions[27 + NUM_ELEMENTS(Narsese_RuleTableVars)] = {0};
        Term subtree = {0};
        if (term1.atoms[0] != 43) { goto RULE_81; }
        if (term1.atoms[1] != 49) { goto RULE_81; }
        subtree = Term_ExtractSubterm(&term1, 2);
        if ((substitutions[28].atoms[0] != 0 && !Term_Equal(&substitutions[28], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_81; }
        substitutions[28] = subtree;
        subtree = Term_ExtractSubterm(&term1, 3);
        if ((substitutions[32].atoms[0] != 0 && !Term_Equal(&substitutions[32], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_81; }
        substitutions[32] = subtree;
        subtree = Term_ExtractSubterm(&term1, 4);
        if ((substitutions[29].atoms[0] != 0 && !Term_Equal(&substitutions[29], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_81; }
        substitutions[29] = subtree;
        Term conclusion = {0};
        conclusion.atoms[0] = 43;
        if (!Term_OverrideSubterm(&conclusion, 1, &substitutions[32])) { goto RULE_81; }
        conclusion.atoms[2] = 39;
        if (!Term_OverrideSubterm(&conclusion, 5, &substitutions[28])) { goto RULE_81; }
        if (!Term_OverrideSubterm(&conclusion, 6, &substitutions[29])) { goto RULE_81; }
        Truth conclusionTruth = Truth_StructuralDeduction(truth1, truth2);
        NAL_DerivedEvent(RuleTableReduce(conclusion, false), conclusionOccurrence, conclusionTruth, conclusionStamp,
                         currentTime, parentPriority, conceptPriority, occurrenceTimeOffset, validation_concept,
                         validation_cid);
    }

    RULE_81:
    {
        if (doublePremise) { goto RULE_82; }
        Term substitutions[27 + NUM_ELEMENTS(Narsese_RuleTableVars)] = {0};
        Term subtree = {0};
        if (term1.atoms[0] != 43) { goto RULE_82; }
        subtree = Term_ExtractSubterm(&term1, 1);
        if ((substitutions[32].atoms[0] != 0 && !Term_Equal(&substitutions[32], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_82; }
        substitutions[32] = subtree;
        if (term1.atoms[2] != 39) { goto RULE_82; }
        subtree = Term_ExtractSubterm(&term1, 5);
        if ((substitutions[28].atoms[0] != 0 && !Term_Equal(&substitutions[28], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_82; }
        substitutions[28] = subtree;
        subtree = Term_ExtractSubterm(&term1, 6);
        if ((substitutions[29].atoms[0] != 0 && !Term_Equal(&substitutions[29], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_82; }
        substitutions[29] = subtree;
        Term conclusion = {0};
        conclusion.atoms[0] = 43;
        conclusion.atoms[1] = 53;
        if (!Term_OverrideSubterm(&conclusion, 2, &substitutions[29])) { goto RULE_82; }
        if (!Term_OverrideSubterm(&conclusion, 3, &substitutions[32])) { goto RULE_82; }
        if (!Term_OverrideSubterm(&conclusion, 4, &substitutions[28])) { goto RULE_82; }
        Truth conclusionTruth = Truth_StructuralDeduction(truth1, truth2);
        NAL_DerivedEvent(RuleTableReduce(conclusion, false), conclusionOccurrence, conclusionTruth, conclusionStamp,
                         currentTime, parentPriority, conceptPriority, occurrenceTimeOffset, validation_concept,
                         validation_cid);
    }

    RULE_82:
    {
        if (doublePremise) { goto RULE_83; }
        Term substitutions[27 + NUM_ELEMENTS(Narsese_RuleTableVars)] = {0};
        Term subtree = {0};
        if (term1.atoms[0] != 43) { goto RULE_83; }
        if (term1.atoms[1] != 53) { goto RULE_83; }
        subtree = Term_ExtractSubterm(&term1, 2);
        if ((substitutions[29].atoms[0] != 0 && !Term_Equal(&substitutions[29], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_83; }
        substitutions[29] = subtree;
        subtree = Term_ExtractSubterm(&term1, 3);
        if ((substitutions[32].atoms[0] != 0 && !Term_Equal(&substitutions[32], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_83; }
        substitutions[32] = subtree;
        subtree = Term_ExtractSubterm(&term1, 4);
        if ((substitutions[28].atoms[0] != 0 && !Term_Equal(&substitutions[28], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_83; }
        substitutions[28] = subtree;
        Term conclusion = {0};
        conclusion.atoms[0] = 43;
        if (!Term_OverrideSubterm(&conclusion, 1, &substitutions[32])) { goto RULE_83; }
        conclusion.atoms[2] = 39;
        if (!Term_OverrideSubterm(&conclusion, 5, &substitutions[28])) { goto RULE_83; }
        if (!Term_OverrideSubterm(&conclusion, 6, &substitutions[29])) { goto RULE_83; }
        Truth conclusionTruth = Truth_StructuralDeduction(truth1, truth2);
        NAL_DerivedEvent(RuleTableReduce(conclusion, false), conclusionOccurrence, conclusionTruth, conclusionStamp,
                         currentTime, parentPriority, conceptPriority, occurrenceTimeOffset, validation_concept,
                         validation_cid);
    }

    RULE_83:
    {
        if (doublePremise) { goto RULE_84; }
        Term substitutions[27 + NUM_ELEMENTS(Narsese_RuleTableVars)] = {0};
        Term subtree = {0};
        if (term1.atoms[0] != 56) { goto RULE_84; }
        subtree = Term_ExtractSubterm(&term1, 1);
        if ((substitutions[28].atoms[0] != 0 && !Term_Equal(&substitutions[28], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_84; }
        substitutions[28] = subtree;
        if (term1.atoms[2] != 38) { goto RULE_84; }
        Term conclusion = {0};
        if (!Term_OverrideSubterm(&conclusion, 0, &substitutions[28])) { goto RULE_84; }
        Truth conclusionTruth = Truth_Negation(truth1, truth2);
        NAL_DerivedEvent(RuleTableReduce(conclusion, false), conclusionOccurrence, conclusionTruth, conclusionStamp,
                         currentTime, parentPriority, conceptPriority, occurrenceTimeOffset, validation_concept,
                         validation_cid);
    }

    RULE_84:
    {
        if (doublePremise) { goto RULE_85; }
        Term substitutions[27 + NUM_ELEMENTS(Narsese_RuleTableVars)] = {0};
        Term subtree = {0};
        if (term1.atoms[0] != 42) { goto RULE_85; }
        subtree = Term_ExtractSubterm(&term1, 1);
        if ((substitutions[28].atoms[0] != 0 && !Term_Equal(&substitutions[28], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_85; }
        substitutions[28] = subtree;
        subtree = Term_ExtractSubterm(&term1, 2);
        if ((substitutions[29].atoms[0] != 0 && !Term_Equal(&substitutions[29], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_85; }
        substitutions[29] = subtree;
        Term conclusion = {0};
        if (!Term_OverrideSubterm(&conclusion, 0, &substitutions[28])) { goto RULE_85; }
        Truth conclusionTruth = Truth_StructuralDeduction(truth1, truth2);
        NAL_DerivedEvent(RuleTableReduce(conclusion, false), conclusionOccurrence, conclusionTruth, conclusionStamp,
                         currentTime, parentPriority, conceptPriority, occurrenceTimeOffset, validation_concept,
                         validation_cid);
    }

    RULE_85:
    {
        if (doublePremise) { goto RULE_86; }
        Term substitutions[27 + NUM_ELEMENTS(Narsese_RuleTableVars)] = {0};
        Term subtree = {0};
        if (term1.atoms[0] != 42) { goto RULE_86; }
        subtree = Term_ExtractSubterm(&term1, 1);
        if ((substitutions[28].atoms[0] != 0 && !Term_Equal(&substitutions[28], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_86; }
        substitutions[28] = subtree;
        subtree = Term_ExtractSubterm(&term1, 2);
        if ((substitutions[29].atoms[0] != 0 && !Term_Equal(&substitutions[29], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_86; }
        substitutions[29] = subtree;
        Term conclusion = {0};
        if (!Term_OverrideSubterm(&conclusion, 0, &substitutions[29])) { goto RULE_86; }
        Truth conclusionTruth = Truth_StructuralDeduction(truth1, truth2);
        NAL_DerivedEvent(RuleTableReduce(conclusion, false), conclusionOccurrence, conclusionTruth, conclusionStamp,
                         currentTime, parentPriority, conceptPriority, occurrenceTimeOffset, validation_concept,
                         validation_cid);
    }

    RULE_86:;
}

Term RuleTableReduce(Term term1, bool doublePremise) {
    goto RULE_86;
    RULE_86:
    {
        if (doublePremise) { goto RULE_87; }
        Term substitutions[27 + NUM_ELEMENTS(Narsese_RuleTableVars)] = {0};
        Term subtree = {0};
        if (term1.atoms[0] != 43) { goto RULE_87; }
        if (term1.atoms[1] != 40) { goto RULE_87; }
        subtree = Term_ExtractSubterm(&term1, 2);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_87; }
        substitutions[31] = subtree;
        subtree = Term_ExtractSubterm(&term1, 3);
        if ((substitutions[28].atoms[0] != 0 && !Term_Equal(&substitutions[28], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_87; }
        substitutions[28] = subtree;
        subtree = Term_ExtractSubterm(&term1, 4);
        if ((substitutions[28].atoms[0] != 0 && !Term_Equal(&substitutions[28], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_87; }
        substitutions[28] = subtree;
        Term conclusion = {0};
        conclusion.atoms[0] = 43;
        if (!Term_OverrideSubterm(&conclusion, 1, &substitutions[28])) { goto RULE_87; }
        if (!Term_OverrideSubterm(&conclusion, 2, &substitutions[31])) { goto RULE_87; }
        IS_SYSTEM_IN_DEBUG_MODE(fputs("Reduced: ", stdout); Narsese_PrintTerm(&term1); fputs(" -> ", stdout); Narsese_PrintTerm(
                &conclusion); puts("");)
        return conclusion;
    }
    RULE_87:
    {
        if (doublePremise) { goto RULE_88; }
        Term substitutions[27 + NUM_ELEMENTS(Narsese_RuleTableVars)] = {0};
        Term subtree = {0};
        if (term1.atoms[0] != 43) { goto RULE_88; }
        subtree = Term_ExtractSubterm(&term1, 1);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_88; }
        substitutions[31] = subtree;
        if (term1.atoms[2] != 40) { goto RULE_88; }
        subtree = Term_ExtractSubterm(&term1, 5);
        if ((substitutions[28].atoms[0] != 0 && !Term_Equal(&substitutions[28], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_88; }
        substitutions[28] = subtree;
        subtree = Term_ExtractSubterm(&term1, 6);
        if ((substitutions[28].atoms[0] != 0 && !Term_Equal(&substitutions[28], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_88; }
        substitutions[28] = subtree;
        Term conclusion = {0};
        conclusion.atoms[0] = 43;
        if (!Term_OverrideSubterm(&conclusion, 1, &substitutions[31])) { goto RULE_88; }
        if (!Term_OverrideSubterm(&conclusion, 2, &substitutions[28])) { goto RULE_88; }
        IS_SYSTEM_IN_DEBUG_MODE(fputs("Reduced: ", stdout); Narsese_PrintTerm(&term1); fputs(" -> ", stdout); Narsese_PrintTerm(
                &conclusion); puts("");)
        return conclusion;
    }
    RULE_88:
    {
        if (doublePremise) { goto RULE_89; }
        Term substitutions[27 + NUM_ELEMENTS(Narsese_RuleTableVars)] = {0};
        Term subtree = {0};
        if (term1.atoms[0] != 43) { goto RULE_89; }
        if (term1.atoms[1] != 41) { goto RULE_89; }
        subtree = Term_ExtractSubterm(&term1, 2);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_89; }
        substitutions[31] = subtree;
        subtree = Term_ExtractSubterm(&term1, 3);
        if ((substitutions[28].atoms[0] != 0 && !Term_Equal(&substitutions[28], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_89; }
        substitutions[28] = subtree;
        subtree = Term_ExtractSubterm(&term1, 4);
        if ((substitutions[28].atoms[0] != 0 && !Term_Equal(&substitutions[28], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_89; }
        substitutions[28] = subtree;
        Term conclusion = {0};
        conclusion.atoms[0] = 43;
        if (!Term_OverrideSubterm(&conclusion, 1, &substitutions[28])) { goto RULE_89; }
        if (!Term_OverrideSubterm(&conclusion, 2, &substitutions[31])) { goto RULE_89; }
        IS_SYSTEM_IN_DEBUG_MODE(fputs("Reduced: ", stdout); Narsese_PrintTerm(&term1); fputs(" -> ", stdout); Narsese_PrintTerm(
                &conclusion); puts("");)
        return conclusion;
    }
    RULE_89:
    {
        if (doublePremise) { goto RULE_90; }
        Term substitutions[27 + NUM_ELEMENTS(Narsese_RuleTableVars)] = {0};
        Term subtree = {0};
        if (term1.atoms[0] != 43) { goto RULE_90; }
        subtree = Term_ExtractSubterm(&term1, 1);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_90; }
        substitutions[31] = subtree;
        if (term1.atoms[2] != 41) { goto RULE_90; }
        subtree = Term_ExtractSubterm(&term1, 5);
        if ((substitutions[28].atoms[0] != 0 && !Term_Equal(&substitutions[28], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_90; }
        substitutions[28] = subtree;
        subtree = Term_ExtractSubterm(&term1, 6);
        if ((substitutions[28].atoms[0] != 0 && !Term_Equal(&substitutions[28], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_90; }
        substitutions[28] = subtree;
        Term conclusion = {0};
        conclusion.atoms[0] = 43;
        if (!Term_OverrideSubterm(&conclusion, 1, &substitutions[31])) { goto RULE_90; }
        if (!Term_OverrideSubterm(&conclusion, 2, &substitutions[28])) { goto RULE_90; }
        IS_SYSTEM_IN_DEBUG_MODE(fputs("Reduced: ", stdout); Narsese_PrintTerm(&term1); fputs(" -> ", stdout); Narsese_PrintTerm(
                &conclusion); puts("");)
        return conclusion;
    }
    RULE_90:
    {
        if (doublePremise) { goto RULE_91; }
        Term substitutions[27 + NUM_ELEMENTS(Narsese_RuleTableVars)] = {0};
        Term subtree = {0};
        if (term1.atoms[0] != 42) { goto RULE_91; }
        subtree = Term_ExtractSubterm(&term1, 1);
        if ((substitutions[28].atoms[0] != 0 && !Term_Equal(&substitutions[28], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_91; }
        substitutions[28] = subtree;
        subtree = Term_ExtractSubterm(&term1, 2);
        if ((substitutions[28].atoms[0] != 0 && !Term_Equal(&substitutions[28], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_91; }
        substitutions[28] = subtree;
        Term conclusion = {0};
        if (!Term_OverrideSubterm(&conclusion, 0, &substitutions[28])) { goto RULE_91; }
        IS_SYSTEM_IN_DEBUG_MODE(fputs("Reduced: ", stdout); Narsese_PrintTerm(&term1); fputs(" -> ", stdout); Narsese_PrintTerm(
                &conclusion); puts("");)
        return conclusion;
    }
    RULE_91:
    {
        if (doublePremise) { goto RULE_92; }
        Term substitutions[27 + NUM_ELEMENTS(Narsese_RuleTableVars)] = {0};
        Term subtree = {0};
        if (term1.atoms[0] != 43) { goto RULE_92; }
        if (term1.atoms[1] != 41) { goto RULE_92; }
        subtree = Term_ExtractSubterm(&term1, 2);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_92; }
        substitutions[31] = subtree;
        if (term1.atoms[3] != 47) { goto RULE_92; }
        if (term1.atoms[4] != 47) { goto RULE_92; }
        subtree = Term_ExtractSubterm(&term1, 7);
        if ((substitutions[28].atoms[0] != 0 && !Term_Equal(&substitutions[28], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_92; }
        substitutions[28] = subtree;
        if (term1.atoms[8] != 38) { goto RULE_92; }
        subtree = Term_ExtractSubterm(&term1, 9);
        if ((substitutions[29].atoms[0] != 0 && !Term_Equal(&substitutions[29], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_92; }
        substitutions[29] = subtree;
        if (term1.atoms[10] != 38) { goto RULE_92; }
        Term conclusion = {0};
        conclusion.atoms[0] = 43;
        conclusion.atoms[1] = 47;
        if (!Term_OverrideSubterm(&conclusion, 2, &substitutions[31])) { goto RULE_92; }
        if (!Term_OverrideSubterm(&conclusion, 3, &substitutions[28])) { goto RULE_92; }
        if (!Term_OverrideSubterm(&conclusion, 4, &substitutions[29])) { goto RULE_92; }
        IS_SYSTEM_IN_DEBUG_MODE(fputs("Reduced: ", stdout); Narsese_PrintTerm(&term1); fputs(" -> ", stdout); Narsese_PrintTerm(
                &conclusion); puts("");)
        return conclusion;
    }
    RULE_92:
    {
        if (doublePremise) { goto RULE_93; }
        Term substitutions[27 + NUM_ELEMENTS(Narsese_RuleTableVars)] = {0};
        Term subtree = {0};
        if (term1.atoms[0] != 43) { goto RULE_93; }
        subtree = Term_ExtractSubterm(&term1, 1);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_93; }
        substitutions[31] = subtree;
        if (term1.atoms[2] != 41) { goto RULE_93; }
        if (term1.atoms[5] != 47) { goto RULE_93; }
        if (term1.atoms[6] != 47) { goto RULE_93; }
        subtree = Term_ExtractSubterm(&term1, 11);
        if ((substitutions[28].atoms[0] != 0 && !Term_Equal(&substitutions[28], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_93; }
        substitutions[28] = subtree;
        if (term1.atoms[12] != 38) { goto RULE_93; }
        subtree = Term_ExtractSubterm(&term1, 13);
        if ((substitutions[29].atoms[0] != 0 && !Term_Equal(&substitutions[29], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_93; }
        substitutions[29] = subtree;
        if (term1.atoms[14] != 38) { goto RULE_93; }
        Term conclusion = {0};
        conclusion.atoms[0] = 43;
        if (!Term_OverrideSubterm(&conclusion, 1, &substitutions[31])) { goto RULE_93; }
        conclusion.atoms[2] = 47;
        if (!Term_OverrideSubterm(&conclusion, 5, &substitutions[28])) { goto RULE_93; }
        if (!Term_OverrideSubterm(&conclusion, 6, &substitutions[29])) { goto RULE_93; }
        IS_SYSTEM_IN_DEBUG_MODE(fputs("Reduced: ", stdout); Narsese_PrintTerm(&term1); fputs(" -> ", stdout); Narsese_PrintTerm(
                &conclusion); puts("");)
        return conclusion;
    }
    RULE_93:
    {
        if (doublePremise) { goto RULE_94; }
        Term substitutions[27 + NUM_ELEMENTS(Narsese_RuleTableVars)] = {0};
        Term subtree = {0};
        if (term1.atoms[0] != 43) { goto RULE_94; }
        if (term1.atoms[1] != 40) { goto RULE_94; }
        subtree = Term_ExtractSubterm(&term1, 2);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_94; }
        substitutions[31] = subtree;
        if (term1.atoms[3] != 46) { goto RULE_94; }
        if (term1.atoms[4] != 46) { goto RULE_94; }
        subtree = Term_ExtractSubterm(&term1, 7);
        if ((substitutions[28].atoms[0] != 0 && !Term_Equal(&substitutions[28], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_94; }
        substitutions[28] = subtree;
        if (term1.atoms[8] != 38) { goto RULE_94; }
        subtree = Term_ExtractSubterm(&term1, 9);
        if ((substitutions[29].atoms[0] != 0 && !Term_Equal(&substitutions[29], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_94; }
        substitutions[29] = subtree;
        if (term1.atoms[10] != 38) { goto RULE_94; }
        Term conclusion = {0};
        conclusion.atoms[0] = 43;
        conclusion.atoms[1] = 46;
        if (!Term_OverrideSubterm(&conclusion, 2, &substitutions[31])) { goto RULE_94; }
        if (!Term_OverrideSubterm(&conclusion, 3, &substitutions[28])) { goto RULE_94; }
        if (!Term_OverrideSubterm(&conclusion, 4, &substitutions[29])) { goto RULE_94; }
        IS_SYSTEM_IN_DEBUG_MODE(fputs("Reduced: ", stdout); Narsese_PrintTerm(&term1); fputs(" -> ", stdout); Narsese_PrintTerm(
                &conclusion); puts("");)
        return conclusion;
    }
    RULE_94:
    {
        if (doublePremise) { goto RULE_95; }
        Term substitutions[27 + NUM_ELEMENTS(Narsese_RuleTableVars)] = {0};
        Term subtree = {0};
        if (term1.atoms[0] != 43) { goto RULE_95; }
        subtree = Term_ExtractSubterm(&term1, 1);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_95; }
        substitutions[31] = subtree;
        if (term1.atoms[2] != 40) { goto RULE_95; }
        if (term1.atoms[5] != 46) { goto RULE_95; }
        if (term1.atoms[6] != 46) { goto RULE_95; }
        subtree = Term_ExtractSubterm(&term1, 11);
        if ((substitutions[28].atoms[0] != 0 && !Term_Equal(&substitutions[28], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_95; }
        substitutions[28] = subtree;
        if (term1.atoms[12] != 38) { goto RULE_95; }
        subtree = Term_ExtractSubterm(&term1, 13);
        if ((substitutions[29].atoms[0] != 0 && !Term_Equal(&substitutions[29], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_95; }
        substitutions[29] = subtree;
        if (term1.atoms[14] != 38) { goto RULE_95; }
        Term conclusion = {0};
        conclusion.atoms[0] = 43;
        if (!Term_OverrideSubterm(&conclusion, 1, &substitutions[31])) { goto RULE_95; }
        conclusion.atoms[2] = 46;
        if (!Term_OverrideSubterm(&conclusion, 5, &substitutions[28])) { goto RULE_95; }
        if (!Term_OverrideSubterm(&conclusion, 6, &substitutions[29])) { goto RULE_95; }
        IS_SYSTEM_IN_DEBUG_MODE(fputs("Reduced: ", stdout); Narsese_PrintTerm(&term1); fputs(" -> ", stdout); Narsese_PrintTerm(
                &conclusion); puts("");)
        return conclusion;
    }
    RULE_95:
    {
        if (doublePremise) { goto RULE_96; }
        Term substitutions[27 + NUM_ELEMENTS(Narsese_RuleTableVars)] = {0};
        Term subtree = {0};
        if (term1.atoms[0] != 43) { goto RULE_96; }
        if (term1.atoms[1] != 47) { goto RULE_96; }
        subtree = Term_ExtractSubterm(&term1, 2);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_96; }
        substitutions[31] = subtree;
        if (term1.atoms[3] != 50) { goto RULE_96; }
        if (term1.atoms[4] != 38) { goto RULE_96; }
        subtree = Term_ExtractSubterm(&term1, 7);
        if ((substitutions[28].atoms[0] != 0 && !Term_Equal(&substitutions[28], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_96; }
        substitutions[28] = subtree;
        subtree = Term_ExtractSubterm(&term1, 8);
        if ((substitutions[29].atoms[0] != 0 && !Term_Equal(&substitutions[29], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_96; }
        substitutions[29] = subtree;
        Term conclusion = {0};
        conclusion.atoms[0] = 43;
        conclusion.atoms[1] = 47;
        if (!Term_OverrideSubterm(&conclusion, 2, &substitutions[31])) { goto RULE_96; }
        if (!Term_OverrideSubterm(&conclusion, 3, &substitutions[28])) { goto RULE_96; }
        if (!Term_OverrideSubterm(&conclusion, 4, &substitutions[29])) { goto RULE_96; }
        IS_SYSTEM_IN_DEBUG_MODE(fputs("Reduced: ", stdout); Narsese_PrintTerm(&term1); fputs(" -> ", stdout); Narsese_PrintTerm(
                &conclusion); puts("");)
        return conclusion;
    }
    RULE_96:
    {
        if (doublePremise) { goto RULE_97; }
        Term substitutions[27 + NUM_ELEMENTS(Narsese_RuleTableVars)] = {0};
        Term subtree = {0};
        if (term1.atoms[0] != 43) { goto RULE_97; }
        subtree = Term_ExtractSubterm(&term1, 1);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_97; }
        substitutions[31] = subtree;
        if (term1.atoms[2] != 47) { goto RULE_97; }
        if (term1.atoms[5] != 50) { goto RULE_97; }
        if (term1.atoms[6] != 38) { goto RULE_97; }
        subtree = Term_ExtractSubterm(&term1, 11);
        if ((substitutions[28].atoms[0] != 0 && !Term_Equal(&substitutions[28], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_97; }
        substitutions[28] = subtree;
        subtree = Term_ExtractSubterm(&term1, 12);
        if ((substitutions[29].atoms[0] != 0 && !Term_Equal(&substitutions[29], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_97; }
        substitutions[29] = subtree;
        Term conclusion = {0};
        conclusion.atoms[0] = 43;
        if (!Term_OverrideSubterm(&conclusion, 1, &substitutions[31])) { goto RULE_97; }
        conclusion.atoms[2] = 47;
        if (!Term_OverrideSubterm(&conclusion, 5, &substitutions[28])) { goto RULE_97; }
        if (!Term_OverrideSubterm(&conclusion, 6, &substitutions[29])) { goto RULE_97; }
        IS_SYSTEM_IN_DEBUG_MODE(fputs("Reduced: ", stdout); Narsese_PrintTerm(&term1); fputs(" -> ", stdout); Narsese_PrintTerm(
                &conclusion); puts("");)
        return conclusion;
    }
    RULE_97:
    {
        if (doublePremise) { goto RULE_98; }
        Term substitutions[27 + NUM_ELEMENTS(Narsese_RuleTableVars)] = {0};
        Term subtree = {0};
        if (term1.atoms[0] != 43) { goto RULE_98; }
        if (term1.atoms[1] != 46) { goto RULE_98; }
        subtree = Term_ExtractSubterm(&term1, 2);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_98; }
        substitutions[31] = subtree;
        if (term1.atoms[3] != 50) { goto RULE_98; }
        if (term1.atoms[4] != 38) { goto RULE_98; }
        subtree = Term_ExtractSubterm(&term1, 7);
        if ((substitutions[28].atoms[0] != 0 && !Term_Equal(&substitutions[28], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_98; }
        substitutions[28] = subtree;
        subtree = Term_ExtractSubterm(&term1, 8);
        if ((substitutions[29].atoms[0] != 0 && !Term_Equal(&substitutions[29], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_98; }
        substitutions[29] = subtree;
        Term conclusion = {0};
        conclusion.atoms[0] = 43;
        conclusion.atoms[1] = 46;
        if (!Term_OverrideSubterm(&conclusion, 2, &substitutions[31])) { goto RULE_98; }
        if (!Term_OverrideSubterm(&conclusion, 3, &substitutions[28])) { goto RULE_98; }
        if (!Term_OverrideSubterm(&conclusion, 4, &substitutions[29])) { goto RULE_98; }
        IS_SYSTEM_IN_DEBUG_MODE(fputs("Reduced: ", stdout); Narsese_PrintTerm(&term1); fputs(" -> ", stdout); Narsese_PrintTerm(
                &conclusion); puts("");)
        return conclusion;
    }
    RULE_98:
    {
        if (doublePremise) { goto RULE_99; }
        Term substitutions[27 + NUM_ELEMENTS(Narsese_RuleTableVars)] = {0};
        Term subtree = {0};
        if (term1.atoms[0] != 43) { goto RULE_99; }
        subtree = Term_ExtractSubterm(&term1, 1);
        if ((substitutions[31].atoms[0] != 0 && !Term_Equal(&substitutions[31], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_99; }
        substitutions[31] = subtree;
        if (term1.atoms[2] != 46) { goto RULE_99; }
        if (term1.atoms[5] != 50) { goto RULE_99; }
        if (term1.atoms[6] != 38) { goto RULE_99; }
        subtree = Term_ExtractSubterm(&term1, 11);
        if ((substitutions[28].atoms[0] != 0 && !Term_Equal(&substitutions[28], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_99; }
        substitutions[28] = subtree;
        subtree = Term_ExtractSubterm(&term1, 12);
        if ((substitutions[29].atoms[0] != 0 && !Term_Equal(&substitutions[29], &subtree)) ||
            Narsese_copulaEquals(subtree.atoms[0], '@')) { goto RULE_99; }
        substitutions[29] = subtree;
        Term conclusion = {0};
        conclusion.atoms[0] = 43;
        if (!Term_OverrideSubterm(&conclusion, 1, &substitutions[31])) { goto RULE_99; }
        conclusion.atoms[2] = 46;
        if (!Term_OverrideSubterm(&conclusion, 5, &substitutions[28])) { goto RULE_99; }
        if (!Term_OverrideSubterm(&conclusion, 6, &substitutions[29])) { goto RULE_99; }
        IS_SYSTEM_IN_DEBUG_MODE(fputs("Reduced: ", stdout); Narsese_PrintTerm(&term1); fputs(" -> ", stdout); Narsese_PrintTerm(
                &conclusion); puts("");)
        return conclusion;
    }
    RULE_99:;
    return term1;
}

