
target_sources(example-app-tests PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/Common.cc
	${CMAKE_CURRENT_SOURCE_DIR}/TopLeftViewportTest.cc
	${CMAKE_CURRENT_SOURCE_DIR}/CenteredViewportTest.cc
	${CMAKE_CURRENT_SOURCE_DIR}/TopViewFrameTest.cc
	${CMAKE_CURRENT_SOURCE_DIR}/IsometricViewFrameTest.cc
	)

target_include_directories(example-app-tests PUBLIC
	"${CMAKE_CURRENT_SOURCE_DIR}"
	)
