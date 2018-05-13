project(menu)

# add project library and alias it too
add_library(${PROJECT_NAME} STATIC
							src/menu.cxx
			)
add_library(sub::menu ALIAS ${PROJECT_NAME})

# set include directories
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/inc)

# link required libs
target_link_libraries(${PROJECT_NAME} PUBLIC sub::nostl)

