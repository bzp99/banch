project(banch)

add_library(${PROJECT_NAME} INTERFACE)
add_library(sub::banch ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} INTERFACE ${PROJECT_SOURCE_DIR}/inc)

target_link_libraries(${PROJECT_NAME} INTERFACE sub::nostl)

add_subdirectory(src)
