cmake_minimum_required(VERSION 3.15.1)
project(HMMLIB)
 
include_directories(
       ${CMAKE_SOURCE_DIR}/hmmmmlib
       ${CMAKE_SOURCE_DIR}/hmmmmlib/Decoding
       ${CMAKE_SOURCE_DIR}/hmmmmlib/Evaluation
       ${CMAKE_SOURCE_DIR}/hmmmmlib/HMM
       ${CMAKE_SOURCE_DIR}/hmmmmlib/Test
       ${CMAKE_SOURCE_DIR}/hmmmmlib/Training)

file(GLOB SOURCES
       ${PROJECT_SOURCE_DIR}/hmmmmlib/main.c
       ${PROJECT_SOURCE_DIR}/hmmmmlib/Decoding/*.c
       ${PROJECT_SOURCE_DIR}/hmmmmlib/Evaluation/*.c
       ${PROJECT_SOURCE_DIR}/hmmmmlib/HMM/*.c
       ${PROJECT_SOURCE_DIR}/hmmmmlib/Test/*.c
       ${PROJECT_SOURCE_DIR}/hmmmmlib/Training/*.c)

add_executable(HMMLIB ${SOURCES})
