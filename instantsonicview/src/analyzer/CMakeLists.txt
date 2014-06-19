# Retrieve all analyzer source files

file(GLOB
     INSTANTSONICVIEW_ANALYZER_SRC
     *.cc
)

# Expose variables to parent CMake files
set(INSTANTSONICVIEW_ANALYZER_SRC
    ${INSTANTSONICVIEW_ANALYZER_SRC}
    PARENT_SCOPE
)

file(GLOB
     INSTANTSONICVIEW_ANALYZER_HDR
     *.h
)

# Expose variables to parent CMake files
set(INSTANTSONICVIEW_ANALYZER_HDR
    ${INSTANTSONICVIEW_ANALYZER_HDR}
    PARENT_SCOPE
)
