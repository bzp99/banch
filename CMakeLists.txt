# top-level CMakeLists

cmake_minimum_required(VERSION 3.0)
project(subprojects)

# output dir
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# subprojects
add_subdirectory(banch) # main project
add_subdirectory(nostl) # STL workarounds
add_subdirectory(test) # unit testing w/ GTest
