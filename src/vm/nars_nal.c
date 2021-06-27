/* 
 * The MIT License
 *
 * Copyright 2020 The OpenNARS authors.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
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

#include "nars_nal.h"

int g_ruleID = 0;

static void
nal_generate_premises_unifier(int i, Atom atom, int premiseIndex)
{
	if (atom)
	{
		//upper case atoms are treated as variables in the meta rule language
		if (g_narsese_atomNames[atom - 1][0] >= 'A' && g_narsese_atomNames[atom - 1][0] <= 'Z')
		{
			//unification failure by inequal value assignment (value ITEM_AT position i versus previously assigned one), and variable binding
			printf("subtree = term_extract_subterm(&term%d, %d);\n", premiseIndex, i);
			printf(
				"if((substitutions[%d].atoms[0]!=0 && !term_equal(&substitutions[%d], &subtree)) || narsese_copula_equals(subtree.atoms[0], '@')){ goto RULE_%d; }\n",
				atom,
				atom,
				g_ruleID);
			printf("substitutions[%d] = subtree;\n", atom);
		}
		else
		{
			//structural constraint given by copulas ITEM_AT position i
			printf("if(term%d.atoms[%d] != %d){ goto RULE_%d; }\n", premiseIndex, i, atom, g_ruleID);
		}
	}
}

static void
nal_generate_conclusion_substitution(int i, Atom atom)
{
	if (atom)
	{
		if (g_narsese_atomNames[atom - 1][0] >= 'A' && g_narsese_atomNames[atom - 1][0] <= 'Z')
		{
			//conclusion term gets variables substituted
			printf("if(!term_override_subterm(&conclusion,%d,&substitutions[%d])){ goto RULE_%d; }\n",
			       i,
			       atom,
			       g_ruleID);
		}
		else
		{
			//conclusion term inherits structure from meta rule, namely the copula
			printf("conclusion.atoms[%d] = %d;\n", i, atom);
		}
	}
}

static void
nal_generate_conclusion_term(char *premise1, char *premise2, char *conclusion, bool doublePremise)
{
	Term term1 = narsese_term(premise1);
	Term term2 = doublePremise ? narsese_term(premise2) : (Term) {0};
	Term conclusion_term = narsese_term(conclusion);
	printf("RULE_%d:\n{\n", g_ruleID++);
	//skip double/single premise rule if single/double premise
	if (doublePremise)
	{
		printf("if(!doublePremise) { goto RULE_%d; }\n", g_ruleID);
	}
	if (!doublePremise)
	{
		printf("if(doublePremise) { goto RULE_%d; }\n", g_ruleID);
	}
	puts("Term substitutions[27+NUM_ELEMENTS(NARSESE_RULE_TABLE_VARIABLES)] = {0}; Term subtree = {0};"); //27 because of 9 indep, 9 dep, 9 query vars
	for (int i = 0; i < COMPOUND_TERM_SIZE_MAX; i++)
	{
		nal_generate_premises_unifier(i, term1.atoms[i], 1);
	}
	if (doublePremise)
	{
		for (int i = 0; i < COMPOUND_TERM_SIZE_MAX; i++)
		{
			nal_generate_premises_unifier(i, term2.atoms[i], 2);
		}
	}
	puts("Term conclusion = {0};");
	for (int i = 0; i < COMPOUND_TERM_SIZE_MAX; i++)
	{
		nal_generate_conclusion_substitution(i, conclusion_term.atoms[i]);
	}
}

static void
nal_generate_rule(char *premise1, char *premise2, char *conclusion, char *truthFunction, bool doublePremise,
                  bool switchTruthArgs)
{
	nal_generate_conclusion_term(premise1, premise2, conclusion, doublePremise);
	if (switchTruthArgs)
	{
		printf("Truth conclusionTruth = %s(truth2,truth1);\n", truthFunction);
	}
	else
	{
		printf("Truth conclusionTruth = %s(truth1,truth2);\n", truthFunction);
	}
	puts(
		"nal_derived_event(rule_table_reduce(conclusion, false), conclusionOccurrence, conclusionTruth, conclusionStamp, g_currentTime, parentPriority, conceptPriority, occurrenceTimeOffset, validation_concept, validation_cid);}\n");
}

static void
nal_generate_reduction(char *premise1, char *conclusion)
{
	nal_generate_conclusion_term(premise1, NULL, conclusion, false);
	puts(
		"IS_SYSTEM_IN_DEBUG_MODE( fputs(\"Reduced: \", stdout); Narsese_PrintTerm(&term1); fputs(\" -> \", stdout); io_narsese_print_term(&conclusion); puts(\"\"); ) \nreturn conclusion;\n}");
}

void
nal_generate_rule_table()
{
	puts("#include \"ruletable.h\"");
	puts(
		"void rule_table_apply(Term term1, Term term2, Truth truth1, Truth truth2, long conclusionOccurrence, double occurrenceTimeOffset, Stamp conclusionStamp, long g_currentTime, double parentPriority, double conceptPriority, bool doublePremise, Concept *validation_concept, long validation_cid)\n{\ngoto RULE_0;");
#define H_NAL_RULES

#include "nars_nal.h"

#undef H_NAL_RULES
	printf("RULE_%d:;\n}\n", g_ruleID);
	printf("Term rule_table_reduce(Term term1, bool doublePremise)\n{\ngoto RULE_%d;\n", g_ruleID);
#define H_NAL_REDUCTIONS

#include "nars_nal.h"

#undef H_NAL_REDUCTIONS
	printf("RULE_%d:;\nreturn term1;\n}\n\n", g_ruleID);
}

static int g_atomsCounter = 1; //allows to avoid memset
static int g_atomsAppeared[ATOMS_MAX] = {0};

static bool
nal_atom_appears_twice(Term *conclusionTerm)
{
	if (narsese_copula_equals(conclusionTerm->atoms[0], ':') ||
		narsese_copula_equals(conclusionTerm->atoms[0], '=')) //similarity or inheritance
	{
		g_atomsCounter++;
		for (int i = 0; i < COMPOUND_TERM_SIZE_MAX; i++)
		{
			Atom atom = conclusionTerm->atoms[i];
			if (g_atomsAppeared[conclusionTerm->atoms[i]] == g_atomsCounter) //atom already appeared
			{
				return true;
			}
			if (narsese_is_non_copula_atom(atom))
			{
				g_atomsAppeared[atom] = g_atomsCounter;
			}
		}
	}
	return false;
}

void
nal_derived_event(Term conclusionTerm, long conclusionOccurrence, Truth conclusionTruth, Stamp stamp, long currentTime,
                  double parentPriority, double conceptPriority, double occurrenceTimeOffset,
                  Concept *validation_concept, long validation_cid)
{
	Event e = {.term = conclusionTerm,
		.type = EVENT_TYPE_BELIEF,
		.truth = conclusionTruth,
		.stamp = stamp,
		.occurrenceTime = conclusionOccurrence,
		.creationTime = currentTime};
	if (validation_concept == NULL || validation_concept->id == validation_cid)
	{
		//concept recycling would invalidate the derivation (allows to lock only adding results to memory)
		if (!nal_atom_appears_twice(&conclusionTerm))
		{
			memory_add_event(&e, currentTime, conceptPriority * parentPriority * truth_expectation(conclusionTruth),
			                 occurrenceTimeOffset, false, true, false, false, false);
		}
	}
}
