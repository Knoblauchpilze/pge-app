
target_include_directories(unitTests PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
	)

add_subdirectory(
	${CMAKE_CURRENT_SOURCE_DIR}/app
	)

add_subdirectory(
	${CMAKE_CURRENT_SOURCE_DIR}/coordinates
	)
