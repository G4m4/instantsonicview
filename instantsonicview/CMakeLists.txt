# @brief InstantSonicView root cmake file

add_subdirectory(implementation)
add_subdirectory(src)

if (${INSTANTSONICVIEW_HAS_GTEST} STREQUAL "ON")
  add_subdirectory(tests)
endif (${INSTANTSONICVIEW_HAS_GTEST} STREQUAL "ON")
