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

#include "nars_globals.h"
#include "lib_slog.h"
#include <stdio.h>
#include <stdlib.h>

void
globals_assert(bool b, char *message)
{
	if (!b)
	{
		slog_error(message);
		slog_error("Test failed. The system will now exit. Sorry!");
		exit(1);
	}
}

HASH_TYPE
globals_hash(HASH_TYPE *data, int pieces)
{
	HASH_TYPE hash = 0;
	for (int i = 0; i < pieces; i++, data++)
	{
		hash ^= *data;
		hash += ~(hash << 15);
		hash ^= (hash >> 10);
		hash += (hash << 3);
		hash ^= (hash >> 6);
		hash += ~(hash << 11);
		hash ^= (hash >> 16);
	}
	return hash;
}

//rand(): http://man7.org/linux/man-pages/man3/rand.3.html
//"POSIX.1-2001 gives the following example of an implementation of rand() and srand(), possibly useful when one needs the same sequence on two different machines."
static unsigned long next = 1;

/* RAND_MAX assumed to be 32767 */
int
globals_next_rand(void)
{
	next = next * 1103515245 + 12345;
	return ((unsigned) (next / 65536) % 32768);
}

void
globals_sys_rand(unsigned int seed)
{
	next = seed;
}
