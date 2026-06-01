cmake_minimum_required(VERSION 3.10)
project(PCBNetworkOptimizationTests C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

if(CMAKE_C_COMPILER_ID STREQUAL "GNU" OR CMAKE_C_COMPILER_ID STREQUAL "Clang")
    add_compile_options(-Wall -Wextra)
endif()

set(CORE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../core)
set(ALGO_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../algorithms)

set(CORE_SOURCES
    ${CORE_DIR}/graph.c
    ${CORE_DIR}/Queue.c
    ${CORE_DIR}/Stack.c
    ${CORE_DIR}/Bfs.c
    ${CORE_DIR}/Dfs.c
    ${CORE_DIR}/Connectedness.c
    ${CORE_DIR}/union_find.c
)

set(ALGO_SOURCES
    ${ALGO_DIR}/kruskal.c
)

enable_testing()

# Helper: define a test executable and register it with CTest.
function(pcb_add_test name)
    add_executable(${name} ${ARGN})
    target_include_directories(${name} PRIVATE ${CORE_DIR} ${ALGO_DIR})
    add_test(NAME ${name} COMMAND ${name})
endfunction()

# Unit tests
pcb_add_test(test_queue          test_queue.c          ${CORE_DIR}/Queue.c)
pcb_add_test(test_stack          test_stack.c          ${CORE_DIR}/Stack.c)
pcb_add_test(test_graph          test_graph.c          ${CORE_DIR}/graph.c)
pcb_add_test(test_bfs            test_bfs.c            ${CORE_DIR}/Bfs.c   ${CORE_DIR}/Queue.c)
pcb_add_test(test_dfs            test_dfs.c            ${CORE_DIR}/Dfs.c   ${CORE_DIR}/Stack.c ${CORE_DIR}/graph.c)
pcb_add_test(test_connectedness  test_connectedness.c  ${CORE_DIR}/Connectedness.c ${CORE_DIR}/Dfs.c ${CORE_DIR}/Stack.c ${CORE_DIR}/graph.c)

# Algorithm tests
pcb_add_test(kruskal_test
    kruskal_test.c
    ${CORE_DIR}/graph.c
    ${CORE_DIR}/union_find.c
    ${ALGO_DIR}/kruskal.c
)

# End-to-end demo (graph -> connectedness -> kruskal -> verify)
pcb_add_test(pcb_demo
    pcb_demo.c
    ${CORE_DIR}/graph.c
    ${CORE_DIR}/Connectedness.c
    ${CORE_DIR}/Dfs.c
    ${CORE_DIR}/Stack.c
    ${CORE_DIR}/union_find.c
    ${ALGO_DIR}/kruskal.c
)

# Convenience target: build every test in one shot.
add_custom_target(all_tests
    DEPENDS
        test_queue
        test_stack
        test_graph
        test_bfs
        test_dfs
        test_connectedness
        kruskal_test
        pcb_demo
)
