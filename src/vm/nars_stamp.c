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

#include "nars_stamp.h"

Stamp
stamp_make(Stamp *stamp1, Stamp *stamp2)
{
	Stamp ret = {0};
	bool processStamp1 = true;
	bool processStamp2 = true;
	for (int j = 0, i = 0; i < STAMP_SIZE; i++)
	{
		if (processStamp1)
		{
			if (stamp1->evidentialBase[i] != STAMP_FREE)
			{
				ret.evidentialBase[j] = stamp1->evidentialBase[i];
				j++;
				if (j >= STAMP_SIZE)
				{
					break;
				}
			}
			else
			{
				processStamp1 = false;
			}
		}
		if (processStamp2)
		{
			if (stamp2->evidentialBase[i] != STAMP_FREE)
			{
				ret.evidentialBase[j] = stamp2->evidentialBase[i];
				j++;
				if (j >= STAMP_SIZE)
				{
					break;
				}
			}
			else
			{
				processStamp2 = false;
			}
		}
		if (!processStamp1 && !processStamp2)
		{
			break;
		}
	}
	return ret;
}

bool
stamp_check_overlap(Stamp *a, Stamp *b)
{
	for (int i = 0; i < STAMP_SIZE; i++)
	{
		if (a->evidentialBase[i] == STAMP_FREE)
		{
			break;
		}
		for (int j = 0; j < STAMP_SIZE; j++)
		{
			if (b->evidentialBase[j] == STAMP_FREE)
			{
				break;
			}
			if (a->evidentialBase[i] == b->evidentialBase[j])
			{
				return true;
			}
		}
	}
	return false;
}

void
stamp_print(Stamp *stamp)
{
	fputs("stamp=", stdout);
	for (int i = 0; i < STAMP_SIZE; i++)
	{
		if (stamp->evidentialBase[i] == STAMP_FREE)
		{
			break;
		}
		printf("%ld,", stamp->evidentialBase[i]);
	}
	puts("");
}
