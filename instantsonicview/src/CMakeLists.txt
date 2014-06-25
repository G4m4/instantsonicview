# @brief InstantSonicView main source folder cmake file

include_directories(
  ${CHARTREUSE_INCLUDE_DIR}
  ${INSTANTSONICVIEW_INCLUDE_DIR}
)

# Retrieve source files from subdirectories
add_subdirectory(analyzer)

# Group sources
source_group("analyzer"
  FILES
  ${INSTANTSONICVIEW_ANALYZER_SRC}
  ${INSTANTSONICVIEW_ANALYZER_HDR}
)

# Sources
set(INSTANTSONICVIEW_SRC
  ${INSTANTSONICVIEW_ANALYZER_SRC}
)
set(INSTANTSONICVIEW_HDR
  configuration.h
  common.h
  ${INSTANTSONICVIEW_ANALYZER_HDR}
)

# Target
add_library(instantsonicview_lib
  ${INSTANTSONICVIEW_SRC}
  ${INSTANTSONICVIEW_HDR}
)

set_target_mt(instantsonicview_lib)
