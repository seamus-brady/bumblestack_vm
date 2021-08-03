# Copyright 2021 seamus@bumblestack.com, Corvideon Limited.
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.

from parsimonious import Grammar

grammar = Grammar(
    """
    task ::= sentence
    sentence ::= belief | question | goal 
    belief ::= statement '. [tense] [truth]
    goal ::= statement '! [tense] [desire] 
    question ::= statement '? [tense]
    statement ::= compound-statement [ copula compound-statement ]
    copula ::== '--> | '<-> | '==> | '=/> | '=|>
    compound-statement ::=   ['!] compound-term [ statement-operator compound-term ] | ['!] statement-operator compound-term compound-term  // Infix vs Prefix
    statement-operator ::= '&& | '&/ | '&|
    compound-term ::=   term [ term-operator term ]  | term-operator term term	    // Infix vs Prefix
    term-operator ::== '& | '| | '- | '~ | '* | '/1 | '/2 | '\1 | '\2
    term ::= ['^] word | set | var | ( statement ) | < statement >
    set ::= '{ term [term] '} | '[ term [term] ']
    var ::= '$ word | '# word | '? word
    word ::= { letter | digit | _ | ” | ' }+
    truth ::= '{ float float '}
    desire ::= '{ float float '}
    tense ::= ':|: //indicating "current time
    """)
print(grammar.parse('((bold stuff))'))