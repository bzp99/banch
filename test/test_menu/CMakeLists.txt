# collect source files
file(GLOB SRCS *.cxx)

# create executable
add_executable(test_menu ${SRCS})

# link required lib
target_link_libraries(test_menu sub::menu)

# add test
add_test(NAME test_menu COMMAND test_menu)
