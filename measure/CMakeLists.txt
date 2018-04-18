project(measure)

add_library(${PROJECT_NAME} INTERFACE)
add_library(sub::measure ALIAS ${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} INTERFACE sub::nostl)

target_include_directories(${PROJECT_NAME} INTERFACE ${PROJECT_SOURCE_DIR}/inc)

