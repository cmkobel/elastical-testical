cmake_minimum_required(VERSION 3.7.2)
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
       ${PROJECT_SOURCE_DIR}/src/Decoding/*.h
       ${PROJECT_SOURCE_DIR}/src/Evaluation/*.c
       ${PROJECT_SOURCE_DIR}/src/Evaluation/*.h
       ${PROJECT_SOURCE_DIR}/src/HMM/*.c
       ${PROJECT_SOURCE_DIR}/src/HMM/*.h
       ${PROJECT_SOURCE_DIR}/src/Test/*.c
       ${PROJECT_SOURCE_DIR}/src/Test/*.h
       ${PROJECT_SOURCE_DIR}/src/Training/*.c
       ${PROJECT_SOURCE_DIR}/src/Training/*.h)
#
# Uncomment the following to create a library
#
#add_library(HMMLIB SHARED ${PROJECT_SOURCE_DIR}/src/main_test.c)
#target_link_libraries(HMMLIB m)
#set(CMAKE_POSITION_INDEPENDENT_CODE ON)

#
# Comment the following to create a library
#
add_executable(HMMLIB ${SOURCES})
target_link_libraries(HMMLIB m cblas)

foreach(FILE ${SOURCES}) 
    # Get the directory of the source file
    get_filename_component(PARENT_DIR "${FILE}" DIRECTORY)

    # Remove common directory prefix to make the group
    string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}" "" GROUP "${PARENT_DIR}")

    # Make sure we are using windows slashes
    string(REPLACE "/" "\\" GROUP "${GROUP}")

    # Group into "Source Files" and "Header Files"
    if ("${FILE}" MATCHES ".*\\.cpp")
       set(GROUP "Source Files${GROUP}")
    elseif("${FILE}" MATCHES ".*\\.h")
       set(GROUP "Header Files${GROUP}")
    endif()

    source_group("${GROUP}" FILES "${FILE}")
endforeach()
