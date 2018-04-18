add_executable(${PROJECT_NAME} banch.cxx)

target_link_libraries(${PROJECT_NAME} sub::nostl sub::measure)
