project(banch)

# add the banch library and also alias it as sub::banch
add_library(${PROJECT_NAME} STATIC src/banch.cxx)
add_library(sub::banch ALIAS ${PROJECT_NAME})

# the banch library's includes
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/inc)

# link sub::nostl
target_link_libraries(${PROJECT_NAME} sub::nostl)

# more to do in src
add_subdirectory(src)
