# collect source files
file(GLOB SRCS *.cxx)

# create executable
add_executable(test_nostl ${SRCS})

# link required lib
target_link_libraries(test_nostl sub::nostl)

# add test
add_test(NAME test_nostl COMMAND test_nostl)
