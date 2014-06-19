# Retrieve all VST-specifics source files

file(GLOB
     INSTANTSONICVIEW_PLUGIN_VST_SRC
     *.cc
     *.cpp
)

# Expose variables to parent CMake files
set(INSTANTSONICVIEW_PLUGIN_VST_SRC
    ${INSTANTSONICVIEW_PLUGIN_VST_SRC}
    PARENT_SCOPE
)

file(GLOB
     INSTANTSONICVIEW_PLUGIN_VST_HDR
     *.h
)

# Expose variables to parent CMake files
set(INSTANTSONICVIEW_PLUGIN_VST_HDR
    ${INSTANTSONICVIEW_PLUGIN_VST_HDR}
    PARENT_SCOPE
)
