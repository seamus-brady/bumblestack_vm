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

#include "nars_variable.h"

bool
variable_is_independent_variable(Atom atom)
{
	return atom > 0 && g_narsese_atomNames[(int) atom - 1][1] != 0 && g_narsese_atomNames[(int) atom - 1][0] == '$';
}

bool
variable_is_dependent_variable(Atom atom)
{
	return atom > 0 && g_narsese_atomNames[(int) atom - 1][1] != 0 && g_narsese_atomNames[(int) atom - 1][0] == '#';
}

bool
variable_is_query_variable(Atom atom)
{
	return atom > 0 && g_narsese_atomNames[(int) atom - 1][1] != 0 && g_narsese_atomNames[(int) atom - 1][0] == '?';
}

bool
variable_is_variable(Atom atom)
{
	return variable_is_independent_variable(atom) || variable_is_dependent_variable(atom) || variable_is_query_variable(
		atom);
}

bool
variable_has_variable(Term *term, bool independent, bool dependent, bool query)
{
	for (int i = 0; i < COMPOUND_TERM_SIZE_MAX; i++)
	{
		Atom atom = term->atoms[i];
		if ((independent && variable_is_independent_variable(atom)) ||
			(dependent && variable_is_dependent_variable(atom)) || (query && variable_is_query_variable(atom)))
		{
			return true;
		}
	}
	return false;
}

Substitution
variable_unify2(Term *general, Term *specific, bool unifyQueryVarOnly)
{
	Substitution substitution = {0};
	for (int i = 0; i < COMPOUND_TERM_SIZE_MAX; i++)
	{
		Atom general_atom = general->atoms[i];
		if (general_atom)
		{
			bool is_allowed_var = unifyQueryVarOnly ? variable_is_query_variable(general_atom) : variable_is_variable(
				general_atom);
			if (is_allowed_var)
			{
				ASSERT(general_atom <= 27,
				       "variable_unify: Problematic variable encountered, only $1-$9, #1-#9 and ?1-?9 are allowed!");
				Term subtree = term_extract_subterm(specific, i);
				if (variable_is_query_variable(general_atom) &&
					variable_is_variable(subtree.atoms[0])) //not valid to substitute a variable for a question var
				{
					return substitution;
				}
				if (substitution.map[(int) general_atom].atoms[0] != 0 &&
					!term_equal(&substitution.map[(int) general_atom],
					            &subtree)) //unificiation var consistency criteria
				{
					return substitution;
				}
				if (narsese_copula_equals(subtree.atoms[0], '@')) //not allowed to unify with set terminator
				{
					return substitution;
				}
				substitution.map[(int) general_atom] = subtree;
			}
			else
			{
				if (general_atom != specific->atoms[i]) //inequality since specific atom differs
				{
					return substitution;
				}
			}
		}
	}
	substitution.success = true;
	return substitution;
}

Substitution
variable_unify(Term *general, Term *specific)
{
	return variable_unify2(general, specific, false);
}

Term
variable_apply_substitute(Term term, Substitution substitution, bool *success)
{
	ASSERT(substitution.success,
	       "A substitution from unsuccessful unification cannot be used to substitute variables!");
	*success = true;
	for (int i = 0; i < COMPOUND_TERM_SIZE_MAX; i++)
	{
		Atom general_atom = term.atoms[i];
		bool is_variable = variable_is_variable(general_atom);
		ASSERT(!is_variable || general_atom <= 27,
		       "variable_apply_substitute: Problematic variable encountered, only $1-$9, #1-#9 and ?1-?9 are allowed!");
		if (is_variable && substitution.map[(int) general_atom].atoms[0] != 0)
		{
			if (!term_override_subterm(&term, i, &substitution.map[(int) general_atom]))
			{
				*success = false;
			}
		}
	}
	return term;
}

//Search for variables which appear twice extensionally, if also appearing in the right side of the implication
//then introduce as independent variable, else as dependent variable
static void
variable_count_atoms(Term *cur_inheritance, int *appearing, bool extensionally)
{
	if (narsese_copula_equals(cur_inheritance->atoms[0], ':') ||
		narsese_copula_equals(cur_inheritance->atoms[0], '=')) //inheritance and similarity
	{
		Term side = term_extract_subterm(cur_inheritance, extensionally ? 1 : 2);
		for (int i = 0; i < COMPOUND_TERM_SIZE_MAX; i++)
		{
			Atom atom = side.atoms[i];
			if (narsese_is_non_copula_atom(atom))
			{
				appearing[(int) side.atoms[i]] += 1;
			}
		}
	}
}

Term
variable_introduce_implication_variables(Term implication, bool *success, bool extensionally)
{
	ASSERT(narsese_copula_equals(implication.atoms[0], '$'), "An implication is expected here!");
	Term left_side = term_extract_subterm(&implication, 1);
	Term right_side = term_extract_subterm(&implication, 2);
	int appearing_left[ATOMS_MAX] = {0};
	int appearing_right[ATOMS_MAX] = {0};
	while (narsese_copula_equals(left_side.atoms[0], '+')) //sequence
	{
		Term potential_inheritance = term_extract_subterm(&left_side, 2);
		variable_count_atoms(&potential_inheritance, appearing_left, extensionally);
		left_side = term_extract_subterm(&left_side, 1);
	}
	variable_count_atoms(&left_side, appearing_left, extensionally);
	variable_count_atoms(&right_side, appearing_right, extensionally);
	char depvar_i = 1;
	char indepvar_i = 1;
	char variable_id[ATOMS_MAX] = {0};
	Term implication_copy = implication;
	for (int i = 0; i < COMPOUND_TERM_SIZE_MAX; i++)
	{
		Atom atom = implication_copy.atoms[i];
		if (appearing_left[(int) atom] >= 2 || (appearing_left[(int) atom] && appearing_right[(int) atom]))
		{
			if (appearing_right[(int) atom])
			{
				int var_id = variable_id[(int) atom] = variable_id[(int) atom] ? variable_id[(int) atom] : indepvar_i++;
				if (var_id <= 9) //can only introduce up to 9 variables
				{
					char varname[3] = {'$', ('0' + var_id), 0}; //$i
					Term varterm = narsese_atomic_term(varname);
					if (!term_override_subterm(&implication, i, &varterm))
					{
						*success = false;
						return implication;
					}
				}
			}
			else
			{
				int var_id = variable_id[(int) atom] = variable_id[(int) atom] ? variable_id[(int) atom] : depvar_i++;
				if (var_id <= 9) //can only introduce up to 9 variables
				{
					char varname[3] = {'#', ('0' + var_id), 0}; //#i
					Term varterm = narsese_atomic_term(varname);
					if (!term_override_subterm(&implication, i, &varterm))
					{
						*success = false;
						return implication;
					}
				}
			}
		}

	}
	*success = true;
	return implication;
}

void
variable_normalize(Term *term)
{
	int independent_i = 1, dependent_i = 1, query_i = 1;
	bool normalized[COMPOUND_TERM_SIZE_MAX] = {0};
	//replace variables with numeric representation, then return the term
	for (int j = 0; j < COMPOUND_TERM_SIZE_MAX; j++)
	{
		Atom atom = term->atoms[j];
		char varType = variable_is_independent_variable(atom) ? '$' : (variable_is_dependent_variable(atom) ? '#' : '?');
		int *varIndex = variable_is_independent_variable(atom) ? &independent_i : (variable_is_dependent_variable(atom)
		                                                                         ? &dependent_i : &query_i);
		if (!normalized[j] && variable_is_variable(atom))
		{
			ASSERT(*varIndex <= 9, "Variable overflow in variable normalization!");
			char varname[3] = {varType, ('0' + *varIndex), 0}; //$i, #j, ?k
			(*varIndex)++;
			for (int k = j; k < COMPOUND_TERM_SIZE_MAX; k++)
			{
				Atom atom2 = term->atoms[k];
				if (atom == atom2)
				{
					term->atoms[k] = narsese_atomic_term_index(varname);
					normalized[k] = true;
				}
			}
		}
	}
}
