
find_package (Eigen3 3.4 REQUIRED NO_MODULE)
find_package (GTest REQUIRED)

add_subdirectory (
	${CMAKE_CURRENT_SOURCE_DIR}/unit
	)
