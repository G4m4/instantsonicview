# @brief InstantSonicView implementation root cmake file

add_subdirectory(common)

if (${INSTANTSONICVIEW_HAS_VST} STREQUAL "ON")
  add_subdirectory(plugin)
endif (${INSTANTSONICVIEW_HAS_VST} STREQUAL "ON")

add_subdirectory(standalone)
