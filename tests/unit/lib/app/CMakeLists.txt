
target_sources(example-app-tests PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/ControlsTest.cc
	)

target_include_directories(example-app-tests PUBLIC
	"${CMAKE_CURRENT_SOURCE_DIR}"
	)
