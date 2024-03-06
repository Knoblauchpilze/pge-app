
find_package (Eigen3 3.4 REQUIRED NO_MODULE)
find_package (GTest REQUIRED)
find_package (libpqxx REQUIRED)

add_executable (pge_app_tests)

add_subdirectory(
	${CMAKE_CURRENT_SOURCE_DIR}/unit
	)

target_sources (pge_app_tests PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/main.cc
	)

target_include_directories (pge_app_tests PUBLIC
	${GTEST_INCLUDE_DIRS}
	)

target_link_libraries(pge_app_tests
	core_utils
	pge_app_lib
	Eigen3::Eigen
	${GTEST_LIBRARIES}
	pq
	pqxx
	)
