###
# copied from a GitHub example project
###
file(GLOB SRCS *.cxx)

add_executable(test_banch ${SRCS})

target_link_libraries(test_banch
						libgtest
						libgmock
						sub::banch
)

add_test(NAME test_banch
         COMMAND test_banch
)
