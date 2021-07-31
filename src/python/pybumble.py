import ctypes


class PyBumble:

    def __init__(self):
        pass

    @ctypes.CFUNCTYPE(None)
    def callback(self):
        print("BumbleVM has finished its job")

    def call(self):
        bumble = ctypes.CDLL("/home/seamus/GitHub/bumblestack-repos/bumblestack_vm/cmake-build-debug/libbumblestack.so")
        bumble.initialise_bumble()
        input_string = ctypes.create_string_buffer(str.encode("verbose-mode on"))
        bumble.app_input(input_string, self.callback)
        input_string = ctypes.create_string_buffer(str.encode("<{SHAPE_1} --> RECTANGLE>. :|:"))
        bumble.app_input(input_string, self.callback)
        bumble.quit_bumble()
