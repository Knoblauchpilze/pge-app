
target_include_directories(pge_app_tests PUBLIC
	"${CMAKE_CURRENT_SOURCE_DIR}"
	)

add_subdirectory(
	${CMAKE_CURRENT_SOURCE_DIR}/app
	)

add_subdirectory(
	${CMAKE_CURRENT_SOURCE_DIR}/coordinates
	)
