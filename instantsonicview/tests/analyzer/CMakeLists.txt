# Retrieve all analyzer tests source files

file(GLOB
     INSTANTSONICVIEW_TESTS_ANALYZER_SRC
     *.cc
)

# Expose variables to parent CMake files
set(INSTANTSONICVIEW_TESTS_ANALYZER_SRC
    ${INSTANTSONICVIEW_TESTS_ANALYZER_SRC}
    PARENT_SCOPE
)
