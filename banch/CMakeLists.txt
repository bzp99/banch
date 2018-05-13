project(banch)

# add project library and also alias it too
add_library(${PROJECT_NAME} STATIC
							src/banch.cxx
							src/interactiveFunctions.cxx
			)
add_library(sub::banch ALIAS ${PROJECT_NAME})

# set include directories
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/inc)

# link required libs
target_link_libraries(${PROJECT_NAME}
						PUBLIC
						sub::menu
						sub::nostl
						)

# more to do in src
add_subdirectory(src)
