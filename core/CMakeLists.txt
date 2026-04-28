cmake_minimum_required(VERSION 3.20)
project(PCB_Network_Optimization C)
set(CMAKE_C_STANDARD 99)

# CLion'un dosyaları tanıması için Hepsini buraya yazmalısın:
add_executable(traversal_test
        Queue.c
        Queue.c
        # Örneğin alttaki dosyaları da oluşturduysan buraya eklemelisin:
        # queue.c
        # stack.c
)