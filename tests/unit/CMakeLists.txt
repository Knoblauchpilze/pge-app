
add_executable (unitTests)

target_sources (unitTests PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/main.cc
	)

add_subdirectory (
	${CMAKE_CURRENT_SOURCE_DIR}/pge
	)

target_include_directories (unitTests PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
	)

target_link_libraries (unitTests
	GTest::gtest_main
	pge_app_interface_test_library
	core_utils
	pge_lib
	)
