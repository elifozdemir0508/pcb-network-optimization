cmake_minimum_required(VERSION 3.10)
project(ProjeTestleri C)


# 1. test_queue.c ile üst klasördeki core/Queue.c dosyasını birleştirir.
add_executable(test_queue test_queue.c ../core/Queue.c)
# 2. test_queue.c içindeki #include "Queue.h" kodunun o dosyayı nerede bulacağını söyler.
target_include_directories(test_queue PRIVATE ../core)

add_executable(test_stack test_stack.c ../core/Stack.c)
target_include_directories(test_stack PRIVATE ../core)