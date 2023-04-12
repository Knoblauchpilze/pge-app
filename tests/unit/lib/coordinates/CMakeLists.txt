
target_sources(example-app-tests PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/TopLeftViewportTest.cpp
	)

target_include_directories(example-app-tests PUBLIC
	"${CMAKE_CURRENT_SOURCE_DIR}"
	)
