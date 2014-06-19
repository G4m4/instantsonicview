# @brief Build InstantSonicView tests executable

# preventing warnings from external source files
include_directories(
  SYSTEM
  ${GTEST_INCLUDE_DIRS}
)

include_directories(
  ${INSTANTSONICVIEW_INCLUDE_DIR}
)

# Include all subdirectories tests source files
add_subdirectory(analyzer)

# Group sources
source_group("analyzer"
  FILES
  ${INSTANTSONICVIEW_TESTS_ANALYZER_SRC}
)

# Source files
set(INSTANTSONICVIEW_TESTS_SRC
    main.cc
    ${INSTANTSONICVIEW_TESTS_ANALYZER_SRC}
)

# Target
add_executable(instantsonicview_tests
  ${INSTANTSONICVIEW_TESTS_SRC}
)

set_target_mt(instantsonicview_tests)

target_link_libraries(instantsonicview_tests
  instantsonicview_lib
  gtest_main
)
