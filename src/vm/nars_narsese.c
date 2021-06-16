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

#include "nars_narsese.h"
#include "nars_nar.h"

//Atomic term names:
char g_narsese_atomNames[ATOMS_MAX][ATOMIC_TERM_LEN_MAX];
char g_narsese_operatorNames[OPERATIONS_MAX][ATOMIC_TERM_LEN_MAX];

//upper bound of multplier 3 given by [ becoming "(' " replacement
#define REPLACEMENT_LEN 3*NARSESE_LEN_MAX

//size for the expanded array with spaces for tokenization, has ITEM_AT most 3 times the amount of chars as the replacement array
#define EXPANSION_LEN REPLACEMENT_LEN*3

//whether the package is g_narseseInitialized
static bool g_narseseInitialized = false;

//g_Self atom, avoids strcmp for checking operator format
Atom g_Self;

int g_operatorIndex = 0;

HashTable g_hashtableAtomsStruct;
VMItem *g_hashtableAtomsStoragePtrs[ATOMS_MAX];
VMItem g_hashtableAtomsStorage[ATOMS_MAX];
VMItem *g_hashtableAtomsHashtable[ATOMS_HASHTABLE_BUCKETS];
int g_termIndex = 0;


//Replace copulas with canonical single-char copulas, including sets and set elements!
char *
narsese_replace_with_canonical_copulas(char *narsese, int n)
{
	static char narsese_replaced[REPLACEMENT_LEN];
	memset(narsese_replaced, ' ', REPLACEMENT_LEN);
	//upper bound of 3 increment given by max. look-ahead of --> becoming :, plus 0 ITEM_AT the end
	ASSERT(n + 3 <= NARSESE_LEN_MAX,
	       "NARSESE_LEN_MAX too small, consider increasing or split input into multiple statements! \n");
	int j = 0;
	for (int i = 0; i < n;)
	{
		if (narsese[i] == ',') //, becomes " "
		{
			narsese_replaced[j] = ' ';
			i++;
			j++;
		}
		else if (narsese[i] == '[') // [ becomes "(' "
		{
			narsese_replaced[j] = '(';
			narsese_replaced[j + 1] = '\'';
			narsese_replaced[j + 2] = ' ';
			i++;
			j += 3;
		}
		else if (narsese[i] == '{') // { becomes '(" '
		{
			narsese_replaced[j] = '(';
			narsese_replaced[j + 1] = '"';
			narsese_replaced[j + 2] = ' ';
			i++;
			j += 3;
		}
		else if (narsese[i] == '}' || narsese[i] == ']' || narsese[i] == '>') // }, ], > becomes )
		{
			narsese_replaced[j] = ')';
			i++;
			j++;
		}
		else if (narsese[i] == '<' && narsese[i + 1] != '-') // < becomes (
		{
			narsese_replaced[j] = '(';
			i++;
			j++;
		}
		else if (i + 1 < n)
		{
			if (narsese[i] == '&' && narsese[i + 1] == '/') // &/ becomes +
			{
				narsese_replaced[j] = '+';
				i += 2;
				j++;
			}
			else if (narsese[i] == '&' && narsese[i + 1] == '|') // &| becomes ;
			{
				narsese_replaced[j] = ';';
				i += 2;
				j++;
			}
			else if (narsese[i] == '&' && narsese[i + 1] == '&') // && becomes ;
			{
				narsese_replaced[j] = ';';
				i += 2;
				j++;
			}
			else if (narsese[i] == '/' && narsese[i + 1] == '1') // /1 becomes /
			{
				narsese_replaced[j] = '/';
				i += 2;
				j++;
			}
			else if (narsese[i] == '/' && narsese[i + 1] == '2') // /2 becomes %
			{
				narsese_replaced[j] = '%';
				i += 2;
				j++;
			}
			else if (narsese[i] == '\\' && narsese[i + 1] == '1') // \1 becomes backslash
			{
				narsese_replaced[j] = '\\';
				i += 2;
				j++;
			}
			else if (narsese[i] == '\\' && narsese[i + 1] == '2') // \2 becomes #
			{
				narsese_replaced[j] = '#';
				i += 2;
				j++;
			}
			else if (i + 2 < n)
			{
				if (narsese[i] == '-' && narsese[i + 1] == '-' && narsese[i + 2] == '>') // --> becomes :
				{
					narsese_replaced[j] = ':';
					i += 3;
					j++;
				}
				else if (narsese[i] == '<' && narsese[i + 1] == '-' && narsese[i + 2] == '>') // <-> becomes =
				{
					narsese_replaced[j] = '=';
					i += 3;
					j++;
				}
				else if (narsese[i] == '=' && narsese[i + 1] == '/' && narsese[i + 2] == '>') // =/> becomes $
				{
					narsese_replaced[j] = '$';
					i += 3;
					j++;
				}
				else if (narsese[i] == '=' && narsese[i + 1] == '=' && narsese[i + 2] == '>') // ==> becomes $
				{
					narsese_replaced[j] = '$';
					i += 3;
					j++;
				}
				else if (narsese[i] == '-' && narsese[i + 1] == '-' && narsese[i + 2] != '>') // -- becomes !
				{
					narsese_replaced[j] = '!';
					i += 3;
					j++;
				}
				else
				{
					goto DEFAULT;
				}
			}
			else
			{
				goto DEFAULT;
			}
		}
		else
		{
			goto DEFAULT;
		}
		continue;
		DEFAULT:
		narsese_replaced[j] = narsese[i]; //default
		i++;
		j++;
	}
	narsese_replaced[j] = 0;
	return narsese_replaced;
}

char *
narsese_expand(char *narsese)
{
	//upper bound being 3* the multiplier of the previous upper bound
	static char narsese_expanded[EXPANSION_LEN];
	memset(narsese_expanded, ' ', EXPANSION_LEN);
	char *narsese_replaced = narsese_replace_with_canonical_copulas(narsese, strlen(narsese));
	int k = 0, n = strlen(narsese_replaced);
	for (int i = 0; i < n; i++)
	{
		bool opener_closer = false;
		if (narsese_replaced[i] == '(' || narsese_replaced[i] == ')')
		{
			k += 1;
			opener_closer = true;
		}
		narsese_expanded[k] = narsese_replaced[i];
		if (narsese_replaced[i] == 0)
		{
			break;
		}
		if (opener_closer)
		{
			k += 1;
		}
		k += 1;
	}
	narsese_expanded[k] = 0;
	return narsese_expanded;
}

//skips one compound term by counting parenthesis (1 for "(", -1 for ")") till counter becomes zero again, returning the component index right after it
int
narsese_skip_compound(char **tokens, int i, int nt)
{
	int parenthesis_cnt =
		0; //incremented for each (, decremented for each ), count will be zero after the compound again
	for (; i < nt; i++)
	{
		if (tokens[i][0] == '(' && tokens[i][1] == 0)
		{
			parenthesis_cnt += 1;
		}
		if (tokens[i][0] == ')' && tokens[i][1] == 0)
		{
			parenthesis_cnt -= 1;
		}
		if (parenthesis_cnt == 0)
		{
			return i + 1;
		}
	}
	return i;
}

char **
narsese_prefix_transform(char *narsese_expanded)
{
	static char *tokens[NARSESE_LEN_MAX + 1]; //there cannot be more tokens than chars
	memset(tokens, 0, (NARSESE_LEN_MAX + 1) * sizeof(char *)); //and last one stays NULL for sure
	char *token = strtok(narsese_expanded, " ");
	int nt = 0, nc = NUM_ELEMENTS(NARSESE_CANONICAL_COPULAS) - 1;
	while (token)
	{
		tokens[nt] = token;
		token = strtok(NULL, " ");
		nt++;
	}
	for (int i = 0; i < nt - 2; i++)
	{
		if (tokens[i][0] == '(' && tokens[i][1] == 0)   //see if it's in prefix form
		{
			for (int k = 0; k < nc; k++)
			{
				if (tokens[i + 1][0] == (int) NARSESE_CANONICAL_COPULAS[k] && tokens[i + 1][1] == 0)
				{
					goto Continue;
				}
			}
			//it's not a copula, so its in infix form, we need to find its copula and put it before tokens[i+1]
			int i2 = narsese_skip_compound(tokens, i + 1, nt);
			if (i2 < nt)
			{
				//1. backup copula token
				char copula = tokens[i2][0];
				//2. shift all tokens forward up to copula position and set the copula to be ITEM_AT i+1 instead
				for (int j = i2; j >= i + 2; j--)
				{
					char *temp = tokens[j];
					tokens[j] = tokens[j - 1];
					tokens[j - 1] = temp;
				}
				tokens[i + 1][0] = copula;
				tokens[i + 1][1] = 0;
			}
		}
		Continue:;
	}
	return tokens;
}

int
narsese_operator_index(char *name)
{
	int ret_index = -1;
	for (int i = 0; i < g_operatorIndex; i++)
	{
		if (!strcmp(g_narsese_operatorNames[i], name))
		{
			ret_index = i + 1;
			break;
		}
	}
	if (ret_index == -1)
	{
		ASSERT(g_operatorIndex < OPERATIONS_MAX, "Too many operators, increase OPERATIONS_MAX!");
		ret_index = g_operatorIndex + 1;
		strncpy(g_narsese_operatorNames[g_operatorIndex], name, ATOMIC_TERM_LEN_MAX);
		g_operatorIndex++;
	}
	return ret_index;
}

//Returns the memoized index of an already seen atomic term
int
narsese_atomic_term_index(char *name)
{
	char blockname[ATOMIC_TERM_LEN_MAX] = {0};
	strncpy(blockname, name, ATOMIC_TERM_LEN_MAX - 1);
	long ret_index = -1;
	void *retptr = hashtable_get(&g_hashtableAtomsStruct, blockname);
	if (retptr != NULL)
	{
		ret_index = (long) retptr; //we got the value
	}
	if (name[0] == '^')
	{
		narsese_operator_index(name);
	}
	if (ret_index == -1)
	{
		ASSERT(g_termIndex < ATOMS_MAX, "Too many terms for NAR");
		ret_index = g_termIndex + 1;
		strncpy(g_narsese_atomNames[g_termIndex], name, ATOMIC_TERM_LEN_MAX - 1);
		hashtable_set(&g_hashtableAtomsStruct, (HASH_TYPE *) g_narsese_atomNames[g_termIndex], (void *) ret_index);
		g_termIndex++;
	}
	return ret_index;
}

//Encodes a binary tree in an array, based on the the S-expression tokenization with prefix order
void
narsese_build_binary_tree(Term *bintree, char **tokens_prefix, int i1, int tree_index, int nt)
{
	if (tokens_prefix[i1][0] == '(' && tokens_prefix[i1][1] == 0)
	{
		int icop = i1 + 1;
		//first argument is given by the copula
		i1 = i1 + 2;
		//second argument has to be searched for
		int i2 = narsese_skip_compound(tokens_prefix, i1, nt);
		bintree->atoms[tree_index - 1] = narsese_atomic_term_index(tokens_prefix[icop]);
		if (i1 < nt)
		{
			narsese_build_binary_tree(bintree, tokens_prefix, i1, tree_index * 2, nt); //left child of tree index
		}
		if (i2 < nt)
		{
			narsese_build_binary_tree(bintree, tokens_prefix, i2, tree_index * 2 + 1, nt); //right child of tree index
		}
	}
	else
	{
		ASSERT(tree_index - 1 < COMPOUND_TERM_SIZE_MAX,
		       "COMPOUND_TERM_SIZE_MAX too small, consider increasing or split input into multiple statements!");
		if (!(tokens_prefix[i1][0] == ')' && tokens_prefix[i1][1] == 0))
		{
			bintree->atoms[tree_index - 1] = narsese_atomic_term_index(tokens_prefix[i1]);
		}
		else
		{
			bintree->atoms[tree_index - 1] = narsese_atomic_term_index(
				"@"); //just use "@" for second element as terminator, while "." acts for "deeper" sets than 2
		}
	}
}

Term
narsese_term(char *narsese)
{
	ASSERT(g_narseseInitialized, "Narsese not g_narseseInitialized, call narsese_init first!");
	//parse Narsese by expanding it, bringing into prefix form, then building a binary tree, and normalizing variables
	Term ret = {0};
	char *narsese_expanded = narsese_expand(narsese);
	char **tokens_prefix = narsese_prefix_transform(narsese_expanded);
	int nt = 0;
	for (; tokens_prefix[nt] != NULL; nt++)
	{
	}
	narsese_build_binary_tree(&ret, tokens_prefix, 0, 1, nt);
	variable_normalize(&ret);
	term_hash(&ret);
	return ret;
}

void
narsese_get_sentence(char *narsese, Term *destTerm, char *punctuation, int *tense, bool *isUserKnowledge, Truth *destTv,
                     double *occurrenceTimeOffset)
{
	ASSERT(g_narseseInitialized, "Narsese not g_narseseInitialized, call narsese_init first!");
	//Handle optional dt=num ITEM_AT beginning of line
	*occurrenceTimeOffset = 0.0;
	char dt[10];
	if (narsese[0] == 'd' && narsese[1] == 't' && narsese[2] == '=') //dt=
	{
		for (unsigned int i = 0; i < strlen(narsese); i++)
		{
			if (i >= 3)
			{
				dt[i - 3] = narsese[i];
			}
			if (narsese[i] == ' ')
			{
				dt[i] = 0;
				narsese = &narsese[i];
				break;
			}
		}
		*occurrenceTimeOffset = atof(dt);
	}
	//Handle the rest of the Narsese:
	char narseseInplace[NARSESE_LEN_MAX] = {0};
	destTv->frequency = NAR_DEFAULT_FREQUENCY;
	destTv->confidence = NAR_DEFAULT_CONFIDENCE;
	int len = strlen(narsese);
	ASSERT(len > 1, "Parsing error: Narsese string too short!");
	ASSERT(len < NARSESE_LEN_MAX, "Parsing error: Narsese string too long!"); //< because of '0' terminated strings
	memcpy(narseseInplace, narsese, len);
	//tv is present if last letter is '}'
	if (len >= 2 && narseseInplace[len - 1] == '}')
	{
		//scan for opening '{'
		int openingIdx;
		for (openingIdx = len - 2; openingIdx >= 0 && narseseInplace[openingIdx] != '{'; openingIdx--);
		ASSERT(narseseInplace[openingIdx] == '{', "Parsing error: Truth value opener not found!");
		double conf, freq;
		sscanf(&narseseInplace[openingIdx], "{%lf %lf}", &freq, &conf);
		destTv->frequency = freq;
		destTv->confidence = conf;
		ASSERT(narseseInplace[openingIdx - 1] == ' ', "Parsing error: Space before truth value required!");
		narseseInplace[openingIdx - 1] = 0; //cut it away for further parsing of term
	}
	//parse event marker, punctuation, and finally the term:
	int str_len = strlen(narseseInplace);
	*tense = 0;
	if (str_len >= 3 && narseseInplace[str_len - 1] == ':' && narseseInplace[str_len - 2] == '|' &&
		narseseInplace[str_len - 3] == ':')
		*tense = 1;
	if (str_len >= 3 && narseseInplace[str_len - 1] == ':' && narseseInplace[str_len - 2] == '\\' &&
		narseseInplace[str_len - 3] == ':')
		*tense = 2;
	if (str_len >= 3 && narseseInplace[str_len - 1] == ':' && narseseInplace[str_len - 2] == '/' &&
		narseseInplace[str_len - 3] == ':')
		*tense = 3;
	*isUserKnowledge = str_len >= 3 && narseseInplace[str_len - 1] == ':' && narseseInplace[str_len - 2] == '@' &&
		narseseInplace[str_len - 3] == ':';
	int punctuation_offset = (*tense || *isUserKnowledge) ? 5 : 1;
	*punctuation = narseseInplace[str_len - punctuation_offset];
	ASSERT(*punctuation == '!' || *punctuation == '?' || *punctuation == '.',
	       "Parsing error: Punctuation has to be belief . goal ! or question ?");
	narseseInplace[str_len - punctuation_offset] = 0; //we will only parse the term before it
	*destTerm = narsese_term(narseseInplace);
}

Term
narsese_sequence(Term *a, Term *b, bool *success)
{
	Term ret = {0};
	ret.atoms[0] = narsese_atomic_term_index("+");
	*success = term_override_subterm(&ret, 1, a) && term_override_subterm(&ret, 2, b);
	return *success ? ret : (Term) {0};
}

Term
narsese_atomic_term(char *name)
{
	int number = narsese_atomic_term_index(name);
	Term ret = {0};
	ret.atoms[0] = number;
	return ret;
}

void
narsese_print_atom(Atom atom)
{
	if (atom)
	{
		if (narsese_copula_equals(atom, ':'))
		{
			fputs("-->", stdout);
		}
		else if (narsese_copula_equals(atom, '$'))
		{
			fputs("=/>", stdout);
		}
		else if (narsese_copula_equals(atom, '+'))
		{
			fputs("&/", stdout);
		}
		else if (narsese_copula_equals(atom, ';'))
		{
			fputs("&|", stdout);
		}
		else if (narsese_copula_equals(atom, '='))
		{
			fputs("<->", stdout);
		}
		else if (narsese_copula_equals(atom, '/'))
		{
			fputs("/1", stdout);
		}
		else if (narsese_copula_equals(atom, '%'))
		{
			fputs("/2", stdout);
		}
		else if (narsese_copula_equals(atom, '\\'))
		{
			fputs("\\1", stdout);
		}
		else if (narsese_copula_equals(atom, '#'))
		{
			fputs("\\2", stdout);
		}
		else
		{
			fputs(g_narsese_atomNames[atom - 1], stdout);
		}
	}
	else
	{
		fputs("@", stdout);
	}
}


void
narsese_print_term_pretty_recursive(Term *term, int index) //start with index=1!
{
	Atom atom = term->atoms[index - 1];
	if (!atom)
	{
		return;
	}
	int child1 = index * 2;
	int child2 = index * 2 + 1;
	bool hasLeftChild = child1 < COMPOUND_TERM_SIZE_MAX && term->atoms[child1 - 1];
	bool hasRightChild = child2 < COMPOUND_TERM_SIZE_MAX && term->atoms[child2 - 1] &&
		!narsese_copula_equals(term->atoms[child2 - 1], '@');
	bool isNegation = narsese_copula_equals(atom, '!');
	bool isExtSet = narsese_copula_equals(atom, '"');
	bool isIntSet = narsese_copula_equals(atom, '\'');
	bool isStatement =
		narsese_copula_equals(atom, '$') || narsese_copula_equals(atom, ':') || narsese_copula_equals(atom, '=');
	if (isExtSet)
	{
		fputs(hasLeftChild ? "{" : "", stdout);
	}
	else if (isIntSet)
	{
		fputs(hasLeftChild ? "[" : "", stdout);
	}
	else if (isStatement)
	{
		fputs(hasLeftChild ? "<" : "", stdout);
	}
	else
	{
		fputs(hasLeftChild ? "(" : "", stdout);
		if (isNegation)
		{
			narsese_print_atom(atom);
			fputs(" ", stdout);
		}
	}
	if (child1 < COMPOUND_TERM_SIZE_MAX)
	{
		narsese_print_term_pretty_recursive(term, child1);
	}
	if (hasRightChild)
	{
		fputs(hasLeftChild ? " " : "", stdout);
	}
	if (!isExtSet && !isIntSet && !narsese_copula_equals(atom, '@'))
	{
		if (!isNegation)
		{
			narsese_print_atom(atom);
			fputs(hasLeftChild ? " " : "", stdout);
		}
	}
	if (child2 < COMPOUND_TERM_SIZE_MAX)
	{
		narsese_print_term_pretty_recursive(term, child2);
	}
	if (isExtSet)
	{
		fputs(hasLeftChild ? "}" : "", stdout);
	}
	else if (isIntSet)
	{
		fputs(hasLeftChild ? "]" : "", stdout);
	}
	else if (isStatement)
	{
		fputs(hasLeftChild ? ">" : "", stdout);
	}
	else
	{
		fputs(hasLeftChild ? ")" : "", stdout);
	}
}

void
narsese_print_term(Term *term)
{
	narsese_print_term_pretty_recursive(term, 1);
}

HASH_TYPE
narsese_string_hash(char *name)
{
	ASSERT(name != NULL, "NULL ptr in narsese_string_hash");
	char buffer[ATOMIC_TERM_LEN_MAX] = {0};
	strncpy(buffer, name, ATOMIC_TERM_LEN_MAX - 1);
	int pieces = ATOMIC_TERM_LEN_MAX / HASH_TYPE_SIZE;
	ASSERT(HASH_TYPE_SIZE * pieces == ATOMIC_TERM_LEN_MAX, "Not a multiple, issue in hash calculation (StringHash)");
	return globals_hash((HASH_TYPE *) buffer, pieces);
}

bool
narsese_string_equal(char *name1, char *name2)
{
	ASSERT(name1 != NULL && name2 != NULL, "NULL ptr in narsese_string_equal");
	return !strcmp(name1, name2);
}

void
narsese_init()
{
	hashtable_init(&g_hashtableAtomsStruct,
	               g_hashtableAtomsStorage,
	               g_hashtableAtomsStoragePtrs,
	               g_hashtableAtomsHashtable,
	               ATOMS_HASHTABLE_BUCKETS,
	               ATOMS_MAX,
	               (Equal) narsese_string_equal,
	               (Hash) narsese_string_hash);
	g_operatorIndex = g_termIndex = 0;
	for (int i = 0; i < ATOMS_MAX; i++)
	{
		memset(&g_narsese_atomNames[i], 0, ATOMIC_TERM_LEN_MAX);
	}
	for (int i = 0; i < OPERATIONS_MAX; i++)
	{
		memset(&g_narsese_operatorNames[i], 0, ATOMIC_TERM_LEN_MAX);
	}
	//index variables ITEM_AT first, these atoms come first as also used by Substitution struct
	for (int i = 1; i <= 9; i++)
	{
		char dep_varname[3] = "#1";
		char indep_varname[3] = "$1";
		char query_varname[3] = "?1";
		query_varname[1] = indep_varname[1] = dep_varname[1] = (char) ('0' + i);
		narsese_atomic_term(dep_varname);
		narsese_atomic_term(indep_varname);
		narsese_atomic_term(query_varname);
	}
	//index rule table variables next:
	for (unsigned int i = 0; i < NUM_ELEMENTS(NARSESE_RULE_TABLE_VARIABLES) - 1; i++)
	{
		char varname[2] = " ";
		varname[0] = NARSESE_RULE_TABLE_VARIABLES[i];
		narsese_atomic_term(varname);
	}
	//index the copulas as well, to make sure these will have same index on next run
	for (int i = 0; i < (int) strlen(NARSESE_CANONICAL_COPULAS); i++)
	{
		char cop[2] = {(NARSESE_CANONICAL_COPULAS[i]), 0};
		narsese_atomic_term_index(cop);
	}
	g_Self = narsese_atomic_term_index("g_Self");
	g_narseseInitialized = true;
}

bool
narsese_copula_equals(Atom atom, char name)
{
	return atom > 0 && g_narsese_atomNames[(int) atom - 1][0] == name && g_narsese_atomNames[(int) atom - 1][1] == 0;
}

bool
narsese_is_operator(Atom atom)
{
	return atom > 0 && g_narsese_atomNames[(int) atom - 1][0] == '^';
}

bool
narsese_is_operation(Term *term) //<(*,{g_Self},x) --> ^op> -> [: * ^op " x _ _ g_Self] or simply ^op
{
	return narsese_is_operator(term->atoms[0]) ||
		(narsese_copula_equals(term->atoms[0], ':') && narsese_copula_equals(term->atoms[1], '*') && //(_ * _) -->
			narsese_is_operator(term->atoms[2]) && //^op
			narsese_copula_equals(term->atoms[3], '"') &&
			(term->atoms[7] == g_Self || variable_is_variable(term->atoms[7]))); //  { g_Self } or { VAR }
}

int
narsese_get_operation_id(Term *term)
{
	if (narsese_copula_equals(term->atoms[0], '+')) //sequence
	{
		Term potential_operator = term_extract_subterm(term, 2); //(a &/ ^op)
		ASSERT(!narsese_copula_equals(potential_operator.atoms[0], '+'),
		       "Sequences should be left-nested encoded, never right-nested!!");
		return narsese_get_operation_id(&potential_operator);
	}
	if (narsese_is_operator(term->atoms[0])) //atomic operator
	{
		return narsese_operator_index(g_narsese_atomNames[(int) term->atoms[0] - 1]);
	}
	if (narsese_is_operation(term)) //an operation, we use the operator atom's index on the right side of the inheritance
	{
		return narsese_operator_index(g_narsese_atomNames[(int) term->atoms[2] - 1]);
	}
	return 0; //not an operation term
}

Term
narsese_get_precondition_without_op(Term *precondition)
{
	if (narsese_copula_equals(precondition->atoms[0], '+'))
	{
		Term potential_op = term_extract_subterm(precondition, 2);
		if (narsese_is_operation(&potential_op))
		{
			return term_extract_subterm(precondition, 1);
		}
	}
	return *precondition;
}

bool
narsese_is_non_copula_atom(Atom atom)
{
	return atom > 0 && (g_narsese_atomNames[(int) atom - 1][0] == '^' ||
		(g_narsese_atomNames[(int) atom - 1][0] >= 'a' && g_narsese_atomNames[(int) atom - 1][0] <= 'z') ||
		(g_narsese_atomNames[(int) atom - 1][0] >= 'A' && g_narsese_atomNames[(int) atom - 1][0] <= 'Z') ||
		(g_narsese_atomNames[(int) atom - 1][0] >= '0' && g_narsese_atomNames[(int) atom - 1][0] <= '9'));
}

bool
narsese_is_simple_atom(Atom atom)
{
	return narsese_is_non_copula_atom(atom) && !variable_is_variable(atom);
}
