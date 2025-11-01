cmake_minimum_required(VERSION 3.10)

project(MyCalculator)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_SOURCE_DIR}/include)

file(GLOB SRC_FILES ${CMAKE_SOURCE_DIR}/src/*.cpp)

add_executable(calculator
    ${CMAKE_SOURCE_DIR}/main.cpp
    ${SRC_FILES}
)

add_subdirectory(plugins/basic_operators)

set_target_properties(calculator PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}
)
