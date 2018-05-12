##########################
### CATCH2 INTEGRATION ###
##########################

find_package(git REQUIRED)
include(ExternalProject)

# add Catch2 as an external project
ExternalProject_Add(
	catch
	PREFIX ${CMAKE_CURRENT_BINARY_DIR}/catch
	GIT_REPOSITORY https://github.com/philsquared/Catch.git
	TIMEOUT 10
	UPDATE_COMMAND ${GIT_EXECUTABLE} pull
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
    LOG_DOWNLOAD ON
	)

# Expose required variable (CATCH_INCLUDE_DIR) to parent scope
ExternalProject_Get_Property(catch source_dir)
set(CATCH_INCLUDE_DIR
	${source_dir}/single_include CACHE INTERNAL "Catch2 include folder")

# tell Catch2 to create a main
add_definitions(-DCATCH_CONFIG_MAIN)

#######################
### TESTS FROM HERE ###
#######################

add_subdirectory(test_nostl)
add_subdirectory(test_menu)
add_subdirectory(test_banch)
