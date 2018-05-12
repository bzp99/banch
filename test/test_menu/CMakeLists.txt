# collect source files
file(GLOB SRCS *.cxx)

# create lib
add_library(test_menu SHARED ${SRCS})

# link required libs
target_link_libraries(test_menu sub::menu catch)
