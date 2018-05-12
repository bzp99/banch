add_subdirectory(test_nostl)
add_subdirectory(test_menu)
add_subdirectory(test_banch)

# main file
add_executable(test_main test_main.cxx test_nostl)

# link catch and tests
target_link_libraries(test_main
						catch
						test_nostl
						test_menu
						test_banch
)

add_test(NAME catchTest COMMAND test_main)
