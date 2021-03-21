
target_sources (pge_app_lib PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/Game.cc
  )

target_include_directories (pge_app_lib PUBLIC
  "${CMAKE_CURRENT_SOURCE_DIR}"
  )
