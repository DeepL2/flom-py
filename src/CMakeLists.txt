cmake_minimum_required(VERSION 3.7)
cmake_policy(SET CMP0048 NEW)

project(flom-py VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(PYBIND11_CPP_STANDARD -std=c++17)

if(NOT CONFIG)
  set(CONFIG Release)
endif()

message(STATUS "Build in ${CONFIG} mode")

if(CONFIG STREQUAL "Debug")
  add_compile_options(-O0 -g3)
elseif(CONFIG STREQUAL "Release")
  add_compile_options(-O3)
endif()

add_subdirectory(third_party/pybind11)
# pybind11 headers produce so many errors with strict compiler options
include_directories(SYSTEM ${PYBIND11_INCLUDE_DIR})

include(cmake/clang-format.cmake)
include(cmake/clang-tidy.cmake)

pybind11_add_module(flom MODULE binding.cpp)
target_link_libraries(flom PRIVATE -lflom)
enable_clang_format(flom)
enable_clang_tidy(flom)
