# top-level CMakeLists

cmake_minimum_required(VERSION 3.0)
project(subprojects)

# C++ version
set(CMAKE_CXX_STANDARD 11)

# compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -Wall -Wextra -pedantic")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-sign-compare")

# output dir
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# testing
enable_testing()

###################
### SUBPROJECTS ###
###################

add_subdirectory(banch) # main project
add_subdirectory(nostl) # STL workarounds
add_subdirectory(menu) # interactive menu
add_subdirectory(test) # unit tests

add_subdirectory(catch) # external project: Catch2

#####################
### DOCUMENTATION ###
#####################
option(BUILD_DOC "Build documentation" ON) # documentation is on by default
find_package(Doxygen)
if (DOXYGEN_FOUND)
    # set input and output files
	set(DOXYGEN_IN ${PROJECT_SOURCE_DIR}/doc/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    # request to configure the file
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    message("Doxygen build started")

    # note the option ALL which allows to build the docs together with the
	# application
    add_custom_target( doc_doxygen ALL
						COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
						WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
						COMMENT "Generating API documentation with Doxygen"
						VERBATIM
	)
else (DOXYGEN_FOUND)
  message("Doxygen needs to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)
