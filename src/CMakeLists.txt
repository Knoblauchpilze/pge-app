
add_executable (pge_app)

add_subdirectory (
	${CMAKE_CURRENT_SOURCE_DIR}/pge
	)

add_subdirectory (
	${CMAKE_CURRENT_SOURCE_DIR}/lib
	)

target_sources (pge_app PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/main.cc
	)

target_include_directories (pge_app PUBLIC
	)

target_link_libraries(pge_app
	pge_app_interface_library
	core_utils
	pge_app_lib
	)

if (${ENABLE_TESTS})
	target_link_libraries (pge_app
		pge_app_interface_test_library
		)
endif ()
