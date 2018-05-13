project(nostl)

# create lib and alias it too
add_library(${PROJECT_NAME} INTERFACE)
add_library(sub::nostl ALIAS ${PROJECT_NAME})

# set include directories
target_include_directories(${PROJECT_NAME} INTERFACE ${PROJECT_SOURCE_DIR}/inc)
