add_executable(banch_main banch_main.cxx)

target_link_libraries(banch_main
						PRIVATE
						sub::banch
						sub::menu
						sub::nostl
						)
