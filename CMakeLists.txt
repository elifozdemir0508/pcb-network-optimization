cmake_minimum_required(VERSION 3.10)
project(PCBNetworkOptimization C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

if(CMAKE_C_COMPILER_ID STREQUAL "GNU" OR CMAKE_C_COMPILER_ID STREQUAL "Clang")
    add_compile_options(-Wall -Wextra)
endif()

set(CORE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/core)
set(ALGO_DIR ${CMAKE_CURRENT_SOURCE_DIR}/algorithms)
set(IO_DIR ${CMAKE_CURRENT_SOURCE_DIR}/io)

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

set(IO_SOURCES
    ${IO_DIR}/io_adapter.c    
)

add_executable(${PROJECT_NAME} main.c ${CORE_SOURCES} ${ALGO_SOURCES} ${IO_SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE m)

target_include_directories(${PROJECT_NAME} PRIVATE ${CORE_DIR} ${ALGO_DIR} ${IO_DIR})

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}"
)