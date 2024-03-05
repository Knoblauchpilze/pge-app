
target_include_directories (bsgalone_client_lib PUBLIC
	"${CMAKE_CURRENT_SOURCE_DIR}"
	)

add_subdirectory (
	${CMAKE_CURRENT_SOURCE_DIR}/menus
	)

add_subdirectory (
	${CMAKE_CURRENT_SOURCE_DIR}/common
	)

target_sources (bsgalone_client_lib PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/IUiHandler.cc
	${CMAKE_CURRENT_SOURCE_DIR}/GameOverScreenUiHandler.cc
	${CMAKE_CURRENT_SOURCE_DIR}/HomeScreenUiHandler.cc
	${CMAKE_CURRENT_SOURCE_DIR}/LoadGameScreenUiHandler.cc
	)
