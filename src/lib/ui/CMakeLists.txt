
target_sources (example-app_lib PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/Action.cc
	${CMAKE_CURRENT_SOURCE_DIR}/BackgroundDesc.cc
	${CMAKE_CURRENT_SOURCE_DIR}/MenuContentDesc.cc
	${CMAKE_CURRENT_SOURCE_DIR}/Menu.cc
	)

target_include_directories (example-app_lib PUBLIC
	"${CMAKE_CURRENT_SOURCE_DIR}"
	)
