cmake_minimum_required(VERSION 3.10)
project(ProjeTestleri C)


# 1. test_queue.c ile üst klasördeki core/Queue.c dosyasını birleştirir.
add_executable(test_queue test_queue.c ../core/Queue.c)
# 2. test_queue.c içindeki #include "Queue.h" kodunun o dosyayı nerede bulacağını söyler.
target_include_directories(test_queue PRIVATE ../core)

add_executable(test_stack test_stack.c ../core/Stack.c)
target_include_directories(test_stack PRIVATE ../core)


add_executable(test_bfs test_bfs.c ../core/Bfs.c ../core/Queue.c)
target_include_directories(test_bfs PRIVATE ../core)

add_executable(test_dfs test_dfs.c ../core/Dfs.c ../core/Stack.c)
target_include_directories(test_dfs PRIVATE ../core)

add_executable(test_graph test_graph.c ../core/graph.c)
target_include_directories(test_graph PRIVATE ../core)