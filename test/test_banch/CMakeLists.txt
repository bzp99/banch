# collect source files
file(GLOB SRCS *.cxx)

# create lib
add_library(test_banch SHARED ${SRCS})

# link required libs
target_link_libraries(test_banch sub::banch catch)
