import ctypes


@ctypes.CFUNCTYPE(None)
def callback():
    print("BumbleVM has finished its job")


bumble = ctypes.CDLL("/home/seamus/GitHub/bumblestack-repos/bumblestack_vm/cmake-build-debug/libbumblestack.so")
bumble.initialise_bumble()
input_string = ctypes.create_string_buffer(str.encode("verbose-mode on"))
bumble.app_input(input_string, callback)
input_string = ctypes.create_string_buffer(str.encode("<{SHAPE_1} --> RECTANGLE>. :|:"))
bumble.app_input(input_string, callback)
bumble.quit_bumble()
