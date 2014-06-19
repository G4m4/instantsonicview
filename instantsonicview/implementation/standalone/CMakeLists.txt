# @brief InstantSonicView standalone root cmake file

set(INSTANTSONICVIEW_STANDALONE_DIR
  ${CMAKE_CURRENT_SOURCE_DIR}
)

include_directories(
  ${INSTANTSONICVIEW_INCLUDE_DIR}
)

# Look for all standalone-specific files
set (INSTANTSONICVIEW_STANDALONE_SRC
  ${INSTANTSONICVIEW_STANDALONE_DIR}/main.cc
)
set (INSTANTSONICVIEW_STANDALONE_HDR
  # Nothing in here for now
)

source_group("instantsonicview" FILES ${INSTANTSONICVIEW_SRC} ${INSTANTSONICVIEW_HDR})
source_group("instantsonicview_implementation" FILES ${INSTANTSONICVIEW_IMPLEMENTATION_SRC} ${INSTANTSONICVIEW_IMPLEMENTATION_HDR})
source_group("standalone_specifics" FILES ${INSTANTSONICVIEW_STANDALONE_SRC} ${INSTANTSONICVIEW_STANDALONE_HDR})

add_executable(instantsonicview
  ${INSTANTSONICVIEW_SRC}
  ${INSTANTSONICVIEW_HDR}
  ${INSTANTSONICVIEW_IMPLEMENTATION_SRC}
  ${INSTANTSONICVIEW_IMPLEMENTATION_HDR}
  ${INSTANTSONICVIEW_STANDALONE_SRC}
  ${INSTANTSONICVIEW_STANDALONE_HDR}
)

target_link_libraries(instantsonicview
                      instantsonicview_lib
)

set_target_mt(instantsonicview)
