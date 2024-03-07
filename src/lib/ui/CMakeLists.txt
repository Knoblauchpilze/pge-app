
target_include_directories (pge_app_lib PUBLIC
	"${CMAKE_CURRENT_SOURCE_DIR}"
	)

add_subdirectory (
	${CMAKE_CURRENT_SOURCE_DIR}/menus
	)

add_subdirectory (
	${CMAKE_CURRENT_SOURCE_DIR}/common
	)

target_sources (pge_app_lib PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/IUiHandler.cc
	${CMAKE_CURRENT_SOURCE_DIR}/GameOverScreenUiHandler.cc
	${CMAKE_CURRENT_SOURCE_DIR}/HomeScreenUiHandler.cc
	${CMAKE_CURRENT_SOURCE_DIR}/LoadGameScreenUiHandler.cc
	)
