# Versione minima di CMake necessaria per compilare il progetto
cmake_minimum_required(VERSION 3.20)

# Nome del progetto software
project(esercitazione1)

# Versione di C++ da usare per la compilazione (C++20)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Opzioni di compilazione per incrementare il livello di warning
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wshadow")

# Eseguibile per il calcolo della media delle temperature da file
add_executable(media_temp media_temp.cpp)

# Eseguibile per la lettura delle temperature da terminale
add_executable(terminal_input terminal_input.cpp)
