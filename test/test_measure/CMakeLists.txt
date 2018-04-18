###
# copied from a GitHub example project
###
file(GLOB SRCS *.cxx)

add_executable(test_nostl ${SRCS})

target_link_libraries(test_measure
						libgtest
						libgmock
						sub::measure
)

add_test(NAME test_measure
         COMMAND test_measure
)
