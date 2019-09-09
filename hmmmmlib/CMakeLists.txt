cmake_minimum_required(VERSION 3.15.1)
project(HMMLIB)
 
include_directories(
       ${CMAKE_SOURCE_DIR}/src
       ${CMAKE_SOURCE_DIR}/src/Decoding
       ${CMAKE_SOURCE_DIR}/src/Evaluation
       ${CMAKE_SOURCE_DIR}/src/HMM
       ${CMAKE_SOURCE_DIR}/src/Test
       ${CMAKE_SOURCE_DIR}/src/Training)

file(GLOB SOURCES
       ${PROJECT_SOURCE_DIR}/src/main.c
       ${PROJECT_SOURCE_DIR}/src/Decoding/*.c
       ${PROJECT_SOURCE_DIR}/src/Evaluation/*.c
       ${PROJECT_SOURCE_DIR}/src/HMM/*.c
       ${PROJECT_SOURCE_DIR}/src/Test/*.c
       ${PROJECT_SOURCE_DIR}/src/Training/*.c)

add_executable(HMMLIB ${SOURCES})
