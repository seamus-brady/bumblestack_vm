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
include_directories(src/c)
include_directories(src/c/system_tests)
include_directories(src/c/unit_tests)
include_directories(src/c/test)
include_directories(src/c/gravity/compiler)
include_directories(src/c/gravity/shared)
include_directories(src/c/gravity/runtime)
include_directories(src/c/gravity/utils)
include_directories(src/c/gravity/optionals)
file(GLOB SRC_FILES
        ${PROJECT_SOURCE_DIR}/*.h
        ${PROJECT_SOURCE_DIR}/*.c)

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
        # gravity lang files
        src/c/gravity/compiler/debug_macros.h
        src/c/gravity/compiler/gravity_ast.c
        src/c/gravity/compiler/gravity_ast.h
        src/c/gravity/compiler/gravity_codegen.c
        src/c/gravity/compiler/gravity_codegen.h
        src/c/gravity/compiler/gravity_compiler.c
        src/c/gravity/compiler/gravity_compiler.h
        src/c/gravity/compiler/gravity_ircode.c
        src/c/gravity/compiler/gravity_ircode.h
        src/c/gravity/compiler/gravity_lexer.c
        src/c/gravity/compiler/gravity_lexer.h
        src/c/gravity/compiler/gravity_optimizer.c
        src/c/gravity/compiler/gravity_optimizer.h
        src/c/gravity/compiler/gravity_parser.c
        src/c/gravity/compiler/gravity_parser.h
        src/c/gravity/compiler/gravity_semacheck1.c
        src/c/gravity/compiler/gravity_semacheck1.h
        src/c/gravity/compiler/gravity_semacheck2.c
        src/c/gravity/compiler/gravity_semacheck2.h
        src/c/gravity/compiler/gravity_symboltable.c
        src/c/gravity/compiler/gravity_symboltable.h
        src/c/gravity/compiler/gravity_token.c
        src/c/gravity/compiler/gravity_token.h
        src/c/gravity/compiler/gravity_visitor.c
        src/c/gravity/compiler/gravity_visitor.h
        src/c/gravity/optionals/gravity_opt_env.c
        src/c/gravity/optionals/gravity_opt_env.h
        src/c/gravity/optionals/gravity_opt_file.c
        src/c/gravity/optionals/gravity_opt_file.h
        src/c/gravity/optionals/gravity_optionals.h
        src/c/gravity/optionals/gravity_opt_json.c
        src/c/gravity/optionals/gravity_opt_json.h
        src/c/gravity/optionals/gravity_opt_math.c
        src/c/gravity/optionals/gravity_opt_math.h
        src/c/gravity/runtime/gravity_core.c
        src/c/gravity/runtime/gravity_core.h
        src/c/gravity/runtime/gravity_vm.c
        src/c/gravity/runtime/gravity_vm.h
        src/c/gravity/runtime/gravity_vmmacros.h
        src/c/gravity/shared/gravity_array.h
        src/c/gravity/shared/gravity_config.h
        src/c/gravity/shared/gravity_delegate.h
        src/c/gravity/shared/gravity_hash.c
        src/c/gravity/shared/gravity_hash.h
        src/c/gravity/shared/gravity_macros.h
        src/c/gravity/shared/gravity_memory.c
        src/c/gravity/shared/gravity_memory.h
        src/c/gravity/shared/gravity_opcodes.h
        src/c/gravity/shared/gravity_value.c
        src/c/gravity/shared/gravity_value.h
        src/c/gravity/utils/gravity_debug.c
        src/c/gravity/utils/gravity_debug.h
        src/c/gravity/utils/gravity_json.c
        src/c/gravity/utils/gravity_json.h
        src/c/gravity/utils/gravity_utils.c
        src/c/gravity/utils/gravity_utils.h
        )

set_target_properties(bumblestack PROPERTIES LINKER_LANGUAGE C)
target_link_libraries(bumblestack m)

######################################################################################################################
### Target for generating ruletable.c
######################################################################################################################
add_executable(generate
        src/c/generate_ruletable/generate.c)

set_target_properties(generate PROPERTIES LINKER_LANGUAGE C)
target_link_libraries(generate m)