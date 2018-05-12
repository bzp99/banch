# collect source files
file(GLOB SRCS *.cxx)

# create executable
add_executable(test_banch ${SRCS})

# link required lib
target_link_libraries(test_banch sub::banch)

# add test
add_test(NAME test_banch COMMAND test_banch)
