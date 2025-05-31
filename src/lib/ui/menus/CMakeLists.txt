
target_include_directories (pge_app_lib PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
	)

target_sources (pge_app_lib PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/BackgroundConfig.cc
	${CMAKE_CURRENT_SOURCE_DIR}/MenuCommon.cc
	${CMAKE_CURRENT_SOURCE_DIR}/TextConfig.cc
	${CMAKE_CURRENT_SOURCE_DIR}/UiMenu.cc
	${CMAKE_CURRENT_SOURCE_DIR}/UiTextMenu.cc
	${CMAKE_CURRENT_SOURCE_DIR}/UiTimedMenu.cc
	)
