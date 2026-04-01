# Versione minima di CMake necessaria per compilare il progetto
cmake_minimum_required(VERSION 3.20)

# Nome del progetto software
project(esercitazione3)

# Versione di C++ da usare per la compilazione (C++20)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Opzioni di compilazione per incrementare il livello di warning
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wshadow -Werror=vla")

# Eseguibile principale
add_executable(main main.cpp)

# Eseguibile per i test
add_executable(test test.cpp)
