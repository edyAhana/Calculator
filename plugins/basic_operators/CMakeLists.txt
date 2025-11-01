cmake_minimum_required(VERSION 3.10)

project(basic_math)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_library(basic_math SHARED ${SOURCES})

set_target_properties(basic_math PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/plugins
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/plugins
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/plugins
)
