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
        src/vm/bumblevm_app.c
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
        src/vm/lib_slog.h
        src/vm/lib_slog.c
        src/vm/nars_io.h
        src/vm/nars_io.c
        src/vm/bumblevm_app.h
        src/vm/bumblevm_app.c)

set_target_properties(bumblestack PROPERTIES LINKER_LANGUAGE C)
target_link_libraries(bumblestack m)

######################################################################################################################
### Target for generating ruletable.vm
######################################################################################################################
add_executable(generate
        src/vm/generate_ruletable/generate.c)

set_target_properties(generate PROPERTIES LINKER_LANGUAGE C)
target_link_libraries(generate m)