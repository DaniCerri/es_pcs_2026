# Versione minima di CMake necessaria per compilare il progetto
cmake_minimum_required(VERSION 3.20)

# Nome del progetto software
project(esercitazione2)

# Versione di C++ da usare per la compilazione (C++20)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Opzioni di compilazione per incrementare il livello di warning
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wshadow -Werror=vla")

# Eseguibile per l'esercizio 1 (indirizzi di memoria)
add_executable(esercizio1 esercizio1.cpp)

# Eseguibile per l'esercizio 2 (min, max, media, deviazione standard)
add_executable(esercizio2 esercizio2.cpp)

# Eseguibile per il bubble sort
add_executable(bubble_sort bubble_sort.cpp)
