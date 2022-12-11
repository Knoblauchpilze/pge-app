
target_sources (example-app_lib PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/Game.cc
	${CMAKE_CURRENT_SOURCE_DIR}/SavedGames.cc
	${CMAKE_CURRENT_SOURCE_DIR}/GameState.cc
	)

target_include_directories (example-app_lib PUBLIC
	"${CMAKE_CURRENT_SOURCE_DIR}"
	)
