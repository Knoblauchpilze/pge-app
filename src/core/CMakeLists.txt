
add_library (core_lib SHARED "")

set (CMAKE_POSITION_INDEPENDENT_CODE ON)

target_sources (core_lib PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/CoreException.cc
	${CMAKE_CURRENT_SOURCE_DIR}/CoreObject.cc
	${CMAKE_CURRENT_SOURCE_DIR}/SafetyNet.cc
	)

add_subdirectory (
	${CMAKE_CURRENT_SOURCE_DIR}/log
	)

target_include_directories (core_lib PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
	)

target_link_libraries (core_lib PUBLIC
	pge_app_interface_library
	)

if (${ENABLE_TESTS})
	target_link_libraries (core_lib PUBLIC
		pge_app_interface_test_library
		)
endif ()
