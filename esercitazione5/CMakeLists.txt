cmake_minimum_required(VERSION 3.20)
project(esercitazione5)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wshadow -Werror=vla")

# Confronto sui vettori grandi
set(SRC_measure timecounter.cpp measure.cpp)
add_executable(main ${SRC_measure})

# Confronto sui vettori piccoli per stimare la soglia ibrida
set(SRC_measure_small timecounter.cpp measure_small.cpp)
add_executable(measure_small ${SRC_measure_small})

# Test unitari
add_executable(test_mergesort test_mergesort.cpp)
add_test(NAME mergesort COMMAND test_mergesort)

add_executable(test_quicksort test_quicksort.cpp)
add_test(NAME quicksort COMMAND test_quicksort)

enable_testing()
