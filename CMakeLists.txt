######################################################################################################################
### BumbleStack CMake File
######################################################################################################################
cmake_minimum_required(VERSION 3.19)
project(bumblestack C)

######################################################################################################################
### set values
######################################################################################################################
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "-lm -mfpmath=sse -msse2 -pthread -lpthread -D_POSIX_C_SOURCE=199506L -std=c11 -g3 -O3")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(CTEST_BINARY_DIRECTORY ${PROJECT_BINARY_DIR}/tests)
set(CMAKE_BUILD_TYPE Debug)

######################################################################################################################
### include directories
######################################################################################################################
include_directories(src/c)
include_directories(src/c/system_tests)
include_directories(src/c/unit_tests)
include_directories(src/c/test)
include_directories(/home/seamus/bin/emsdk/upstream/emscripten/system/include/emscripten)

######################################################################################################################
### target for unit tests
######################################################################################################################
add_executable(unit_tests
        src/c/test/unit_tests.c
        src/c/test/unity/unity.h
        src/c/test/unity/unity_internals.h
        src/c/test/unity/unity.c
        src/c/test/unit_tests.h)

set_target_properties(unit_tests PROPERTIES LINKER_LANGUAGE C)
target_link_libraries(unit_tests m)

######################################################################################################################
### target for main executable
######################################################################################################################
add_executable(bumblestack
        src/c/buffer.c
        src/c/buffer.h
        src/c/commander.c
        src/c/commander.h
        src/c/concept.h
        src/c/config.h
        src/c/cycle.c
        src/c/cycle.h
        src/c/decision.c
        src/c/decision.h
        src/c/event.c
        src/c/event.h
        src/c/fifo.c
        src/c/fifo.h
        src/c/fs.c
        src/c/fs.h
        src/c/globals.c
        src/c/globals.h
        src/c/hashtable.c
        src/c/hashtable.h
        src/c/implication.h
        src/c/inference.c
        src/c/inference.h
        src/c/invertedAtomIndex.c
        src/c/invertedAtomIndex.h
        src/c/app.c
        src/c/memory.c
        src/c/memory.h
        src/c/nal.c
        src/c/nal.h
        src/c/nar.c
        src/c/nar.h
        src/c/narsese.c
        src/c/narsese.h
        src/c/priorityqueue.c
        src/c/priorityqueue.h
        src/c/ruletable.h
        src/c/ruletable.c
        src/c/shell.c
        src/c/shell.h
        src/c/stack.c
        src/c/stack.h
        src/c/stamp.c
        src/c/stamp.h
        src/c/stats.c
        src/c/stats.h
        src/c/table.c
        src/c/table.h
        src/c/term.c
        src/c/term.h
        src/c/truth.c
        src/c/truth.h
        src/c/usage.c
        src/c/usage.h
        src/c/variable.c
        src/c/variable.h
        src/c/slog.h
        src/c/slog.c
        src/c/io.h
        src/c/io.c
        src/c/app.h
        src/c/app.c
        src/c/scripting.h
        src/c/scripting.c
        # wren embedded scripting language
        src/c/wren_common.h
        src/c/wren_compiler.c
        src/c/wren_compiler.h
        src/c/wren_core.c
        src/c/wren_core.h
        src/c/wren_core.wren
        src/c/wren_core.wren.inc
        src/c/wren_debug.c
        src/c/wren_debug.h
        src/c/wren_math.h
        src/c/wren_opcodes.h
        src/c/wren_primitive.c
        src/c/wren_primitive.h
        src/c/wren_utils.c
        src/c/wren_utils.h
        src/c/wren_value.c
        src/c/wren_value.h
        src/c/wren_vm.c
        src/c/wren_vm.h
        src/c/wren.h
        src/c/wren_opt_meta.c
        src/c/wren_opt_meta.h
        src/c/wren_opt_meta.wren
        src/c/wren_opt_meta.wren.inc
        src/c/wren_opt_random.c
        src/c/wren_opt_random.h
        src/c/wren_opt_random.wren
        src/c/wren_opt_random.wren.inc)

set_target_properties(bumblestack PROPERTIES LINKER_LANGUAGE C)
target_link_libraries(bumblestack m)

######################################################################################################################
### Target for generating ruletable.c - disabled
######################################################################################################################
#add_executable(generate
#        src/c/generate_ruletable/generate.c)
#
#set_target_properties(generate PROPERTIES LINKER_LANGUAGE C)
#target_link_libraries(generate m)