###
# copied from a GitHub example project
###
file(GLOB SRCS *.cxx)

add_executable(test_menu ${SRCS})

target_link_libraries(test_menu
						libgtest
						libgmock
						sub::menu
)

add_test(NAME test_menu
         COMMAND test_menu
)
