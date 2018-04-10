###
# copied from a GitHub example project
###
file(GLOB SRCS *.cxx)

add_executable(test_nostl ${SRCS})

target_link_libraries(test_nostl
						libgtest
						libgmock
						sub::nostl
)

add_test(NAME test_nostl
         COMMAND test_nostl
)
