######################################################################################################################
### BumbleStack CMake File
######################################################################################################################
cmake_minimum_required(VERSION 3.19)
project(bumblestack C)

######################################################################################################################
### set values
######################################################################################################################
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "-lm -mfpmath=sse -msse2 -pthread -lpthread -D_POSIX_C_SOURCE=199506L -pedantic -std=c99 -g3 -O3")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_BUILD_TYPE Debug)

######################################################################################################################
### include directories
######################################################################################################################
include_directories(src/vm)
include_directories(src/vm/system_tests)
include_directories(src/vm/unit_tests)
include_directories(src/vm/test)

######################################################################################################################
### target for unit tests
######################################################################################################################
add_executable(unit_tests
        src/vm/test/unit_tests.c
        src/vm/test/unity/unity.h
        src/vm/test/unity/unity_internals.h
        src/vm/test/unity/unity.c
        src/vm/test/unit_tests.h)

set_target_properties(unit_tests PROPERTIES LINKER_LANGUAGE C)
target_link_libraries(unit_tests m)

######################################################################################################################
### target for main executable
######################################################################################################################
add_executable(bumblestack
        # main bumblevm app
        src/vm/app.c
        src/vm/app.h
        # nars modules
        src/vm/nars_concept.h
        src/vm/nars_config.h
        src/vm/nars_cycle.c
        src/vm/nars_cycle.h
        src/vm/nars_decision.c
        src/vm/nars_decision.h
        src/vm/nars_event.c
        src/vm/nars_event.h
        src/vm/nars_fifo.c
        src/vm/nars_fifo.h
        src/vm/nars_globals.c
        src/vm/nars_globals.h
        src/vm/nars_hashtable.c
        src/vm/nars_hashtable.h
        src/vm/nars_implication.h
        src/vm/nars_inference.c
        src/vm/nars_inference.h
        src/vm/nars_inverted_atom_index.c
        src/vm/nars_inverted_atom_index.h
        src/vm/nars_memory.c
        src/vm/nars_memory.h
        src/vm/nars_nal.c
        src/vm/nars_nal.h
        src/vm/nars_nar.c
        src/vm/nars_nar.h
        src/vm/nars_narsese.c
        src/vm/nars_narsese.h
        src/vm/nars_priority_queue.c
        src/vm/nars_priority_queue.h
        src/vm/nars_ruletable.h
        src/vm/nars_ruletable.c
        src/vm/nars_shell.c
        src/vm/nars_shell.h
        src/vm/nars_stack.c
        src/vm/nars_stack.h
        src/vm/nars_stamp.c
        src/vm/nars_stamp.h
        src/vm/nars_stats.c
        src/vm/nars_stats.h
        src/vm/nars_table.c
        src/vm/nars_table.h
        src/vm/nars_term.c
        src/vm/nars_term.h
        src/vm/nars_truth.c
        src/vm/nars_truth.h
        src/vm/nars_usage.c
        src/vm/nars_usage.h
        src/vm/nars_variable.c
        src/vm/nars_variable.h
        src/vm/nars_io.h
        src/vm/nars_io.c
        # library code
        src/vm/lib_slog.h
        src/vm/lib_slog.c
        src/vm/lib_buffer.h
        src/vm/lib_buffer.c
        # wren embedded scripting language
        src/vm/wren_common.h
        src/vm/wren_compiler.c
        src/vm/wren_compiler.h
        src/vm/wren_core.c
        src/vm/wren_core.h
        src/vm/wren_core.wren
        src/vm/wren_core.wren.inc
        src/vm/wren_debug.c
        src/vm/wren_debug.h
        src/vm/wren_math.h
        src/vm/wren_opcodes.h
        src/vm/wren_primitive.c
        src/vm/wren_primitive.h
        src/vm/wren_utils.c
        src/vm/wren_utils.h
        src/vm/wren_value.c
        src/vm/wren_value.h
        src/vm/wren_vm.c
        src/vm/wren_vm.h
        src/vm/wren.h
        src/vm/wren_opt_meta.c
        src/vm/wren_opt_meta.h
        src/vm/wren_opt_meta.wren.inc
        src/vm/wren_opt_random.c
        src/vm/wren_opt_random.h
        src/vm/wren_opt_random.wren.inc src/vm/app_script_loader.h src/vm/app_script_loader.c)

set_target_properties(bumblestack PROPERTIES LINKER_LANGUAGE C)
target_link_libraries(bumblestack m)

######################################################################################################################
### Target for generating ruletable.vm
######################################################################################################################
add_executable(generate
        src/vm/generate_ruletable/generate.c)

set_target_properties(generate PROPERTIES LINKER_LANGUAGE C)
target_link_libraries(generate m)