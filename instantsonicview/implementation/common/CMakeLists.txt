# Retrieve all implementation common source files

file(GLOB
     INSTANTSONICVIEW_IMPLEMENTATION_SRC
     *.cpp
     *.cc
)

# Expose variables to parent CMake files
set(INSTANTSONICVIEW_IMPLEMENTATION_SRC
    ${INSTANTSONICVIEW_IMPLEMENTATION_SRC}
    PARENT_SCOPE
)

file(GLOB
     INSTANTSONICVIEW_IMPLEMENTATION_HDR
     *.h
)

# Expose variables to parent CMake files
set(INSTANTSONICVIEW_IMPLEMENTATION_HDR
    ${INSTANTSONICVIEW_IMPLEMENTATION_HDR}
    PARENT_SCOPE
)
