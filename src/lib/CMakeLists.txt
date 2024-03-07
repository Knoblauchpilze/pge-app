
add_library (pge_app_lib SHARED "")

set (CMAKE_POSITION_INDEPENDENT_CODE ON)

add_subdirectory (
	${CMAKE_CURRENT_SOURCE_DIR}/game
	)

add_subdirectory (
	${CMAKE_CURRENT_SOURCE_DIR}/inputs
	)

add_subdirectory (
	${CMAKE_CURRENT_SOURCE_DIR}/renderers
	)

add_subdirectory (
	${CMAKE_CURRENT_SOURCE_DIR}/ui
	)

target_sources (pge_app_lib PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/App.cc
	)

target_link_libraries (pge_app_lib
	core_utils
	pge_lib
	)

target_include_directories (pge_app_lib PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
	)
