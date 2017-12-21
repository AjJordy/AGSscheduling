cmake_minimum_required(VERSION 3.5)
project(AlgoritmoGenetico)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Debug)
set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

set(SOURCE_FILES main.cpp file_to_object.cpp file_to_object.h files.h files.cpp Ag.cpp Ag.h Estudante.h Docente.h Sala.h Disciplina.h Curso.h Cromossomo.cpp Cromossomo.h Elemento.cpp Disciplina.cpp)
add_executable(AlgoritmoGenetico ${SOURCE_FILES})
