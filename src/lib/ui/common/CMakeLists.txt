
target_include_directories (pge_app_lib PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
	)

target_sources (pge_app_lib PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/ScreenCommon.cc
	)
