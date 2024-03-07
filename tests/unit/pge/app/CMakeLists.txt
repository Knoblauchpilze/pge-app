
target_sources(pge_app_tests PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/ControlsTest.cc
	)

target_include_directories(pge_app_tests PUBLIC
	"${CMAKE_CURRENT_SOURCE_DIR}"
	)
