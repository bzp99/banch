# collect source files
file(GLOB SRCS *.cxx)

# create lib
add_library(test_nostl SHARED ${SRCS})

# link required libs
target_link_libraries(test_nostl sub::nostl catch)
