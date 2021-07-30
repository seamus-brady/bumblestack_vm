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
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "release")
endif()

######################################################################################################################
### include directories
######################################################################################################################
include_directories(src/c)
include_directories(src/c/system_tests)
include_directories(src/c/unit_tests)
include_directories(src/c/test)
include_directories(src/c/test)

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
add_library(bumblestack SHARED
        # main bumblevm app
        src/c/app.c
        src/c/app.h
        src/c/app_repl.h
        src/c/app_repl.c
        src/c/app_scripts.h
        src/c/app_scripts.c
        # nars modules
        src/c/nars_common_structs.h
        src/c/nars_concept.h
        src/c/app_config.h
        src/c/nars_cycle.c
        src/c/nars_cycle.h
        src/c/nars_decision.c
        src/c/nars_decision.h
        src/c/nars_event.c
        src/c/nars_event.h
        src/c/nars_fifo.c
        src/c/nars_fifo.h
        src/c/nars_globals.c
        src/c/nars_globals.h
        src/c/nars_hashtable.c
        src/c/nars_hashtable.h
        src/c/nars_implication.h
        src/c/nars_inference.c
        src/c/nars_inference.h
        src/c/nars_inverted_atom_index.c
        src/c/nars_inverted_atom_index.h
        src/c/nars_memory.c
        src/c/nars_memory.h
        src/c/nars_nal.c
        src/c/nars_nal.h
        src/c/nars_nar.c
        src/c/nars_nar.h
        src/c/nars_narsese.c
        src/c/nars_narsese.h
        src/c/nars_priority_queue.c
        src/c/nars_priority_queue.h
        src/c/nars_ruletable.h
        src/c/nars_ruletable.c
        src/c/nars_stack.c
        src/c/nars_stack.h
        src/c/nars_stamp.c
        src/c/nars_stamp.h
        src/c/nars_stats.c
        src/c/nars_stats.h
        src/c/nars_table.c
        src/c/nars_table.h
        src/c/nars_term.c
        src/c/nars_term.h
        src/c/nars_truth.c
        src/c/nars_truth.h
        src/c/nars_usage.c
        src/c/nars_usage.h
        src/c/nars_variable.c
        src/c/nars_variable.h
        src/c/nars_io.h
        src/c/nars_io.c
        # library code
        src/c/lib_slog.h
        src/c/lib_slog.c
        src/c/lib_buffer.h
        src/c/lib_buffer.c
        src/c/lib_wildcardcmp.c
        src/c/lib_wildcardcmp.h
        src/c/lib_trim.c
        src/c/lib_trim.h
        src/c/lib_commander.h
        src/c/lib_commander.c
        src/c/lib_fs.c
        src/c/lib_fs.h
        src/c/lib_strsplit.c
        src/c/lib_strsplit.h
        src/c/lib_asprintf.c
        src/c/lib_asprintf.h
        # repl code
        src/c/repl_error.h
        src/c/repl_eval.h
        src/c/repl_init.h
        src/c/repl_loop.h
        src/c/repl_print.h
        src/c/repl_read.h
        src/c/repl_repl.h
        src/c/repl_term.h
        src/c/repl_eval.c
        src/c/repl_init.c
        src/c/repl_loop.c
        src/c/repl_read.c
        src/c/repl_term.c
        src/c/repl_error.c
        src/c/repl_print.c)

set_target_properties(bumblestack
        PROPERTIES
        LINKER_LANGUAGE C
        RUNTIME_OUTPUT_DIRECTORY "../build/bin/")
target_link_libraries(bumblestack m)

######################################################################################################################
### Target for generating ruletable.c
######################################################################################################################
#add_executable(generate
#        src/c/generate_ruletable/generate.c)
#
#set_target_properties(generate PROPERTIES LINKER_LANGUAGE C)
#target_link_libraries(generate m)