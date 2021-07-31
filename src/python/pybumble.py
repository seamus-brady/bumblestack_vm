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


import ctypes

MAX_CONCEPTS = 65536
MAX_ATOMS = 16384
LIB_BUMBLESTACK = "/home/seamus/GitHub/bumblestack-repos/bumblestack_vm/cmake-build-debug/libbumblestack.so"


@ctypes.CFUNCTYPE(None, ctypes.c_char_p)
def callback(returned_c_str):
    print(returned_c_str.decode("utf-8"))


class PyBumble:

    def __init__(self):
        self.bumble = ctypes.CDLL(LIB_BUMBLESTACK)
        self.bumble.initialise_bumble(callback, MAX_CONCEPTS, MAX_ATOMS)

    def run_bumble(self):
        input_string = ctypes.create_string_buffer(str.encode("verbose-mode on"))
        self.bumble.app_input(input_string)
        input_string = ctypes.create_string_buffer(str.encode("<{SHAPE_1} --> RECTANGLE>. :|:"))
        self.bumble.app_input(input_string)
        self.bumble.quit_bumble()


if __name__ == '__main__':
    pybumble = PyBumble()
    pybumble.run_bumble()
