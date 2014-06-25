# @brief InstantSonicView plugin root cmake file

# These have to be defined since JUCE needs it.
# Sometimes they're not passed to the compiler,
# so we're doing it here explicitly.
if (${SYSTEM_IS_LINUX})
  add_definitions(-DLINUX)
elseif (${SYSTEM_IS_WINDOWS})
  add_definitions(-D_WIN32)
endif ()

# Mac OS X being the default case for Juce, nothing more to declare

# On Linux these are required in order to build an audio plugin
if (${SYSTEM_IS_LINUX})
  find_package(Freetype REQUIRED)
  find_package(X11 REQUIRED)
endif (${SYSTEM_IS_LINUX})

set(INSTANTSONICVIEW_PLUGIN_DIR
    ${CMAKE_CURRENT_SOURCE_DIR}
)

include_directories(SYSTEM
  ${FLATCARBON}  # Mac-specific stuff
  ${FREETYPE_INCLUDE_DIRS}  # Linux-specific stuff
  ${JUCE_INCLUDE_DIR}  # Juce library root path
  ${VST_INCLUDE_DIR}  # VST SDK root path
  ${X11_INCLUDE_DIRS}  # Linux-specific stuff
)

include_directories(
  ${CHARTREUSE_INCLUDE_DIR}
  ${INSTANTSONICVIEW_INCLUDE_DIR}
  # This is required since Juce-generated files are looking for files there
  ${INSTANTSONICVIEW_PLUGIN_DIR}/vst
)

# Source files declaration
if(${SYSTEM_IS_MACOSX})
  # On Mac we have to pass through Juce wrappers (.mm files)
  set(INSTANTSONICVIEW_JUCE_SRC
    ${JUCE_INCLUDE_DIR}/modules/juce_audio_basics/juce_audio_basics.mm
    ${JUCE_INCLUDE_DIR}/modules/juce_audio_devices/juce_audio_devices.mm
    ${JUCE_INCLUDE_DIR}/modules/juce_audio_formats/juce_audio_formats.mm
    ${JUCE_INCLUDE_DIR}/modules/juce_audio_plugin_client/VST/juce_VST_Wrapper.mm
    ${JUCE_INCLUDE_DIR}/modules/juce_audio_plugin_client/utility/juce_PluginUtilities.cpp
    ${JUCE_INCLUDE_DIR}/modules/juce_audio_processors/juce_audio_processors.mm
    ${JUCE_INCLUDE_DIR}/modules/juce_audio_utils/juce_audio_utils.mm
    ${JUCE_INCLUDE_DIR}/modules/juce_core/juce_core.mm
    ${JUCE_INCLUDE_DIR}/modules/juce_cryptography/juce_cryptography.mm
    ${JUCE_INCLUDE_DIR}/modules/juce_data_structures/juce_data_structures.mm
    ${JUCE_INCLUDE_DIR}/modules/juce_events/juce_events.mm
    ${JUCE_INCLUDE_DIR}/modules/juce_graphics/juce_graphics.mm
    ${JUCE_INCLUDE_DIR}/modules/juce_gui_basics/juce_gui_basics.mm
    ${JUCE_INCLUDE_DIR}/modules/juce_gui_extra/juce_gui_extra.mm
    ${JUCE_INCLUDE_DIR}/modules/juce_audio_plugin_client/VST/juce_VST_Wrapper.cpp
  )
else()
  set(INSTANTSONICVIEW_JUCE_SRC
    ${JUCE_INCLUDE_DIR}/modules/juce_audio_basics/juce_audio_basics.cpp
    ${JUCE_INCLUDE_DIR}/modules/juce_audio_devices/juce_audio_devices.cpp
    ${JUCE_INCLUDE_DIR}/modules/juce_audio_formats/juce_audio_formats.cpp
    ${JUCE_INCLUDE_DIR}/modules/juce_audio_plugin_client/VST/juce_VST_Wrapper.cpp
    ${JUCE_INCLUDE_DIR}/modules/juce_audio_plugin_client/utility/juce_PluginUtilities.cpp
    ${JUCE_INCLUDE_DIR}/modules/juce_audio_processors/juce_audio_processors.cpp
    ${JUCE_INCLUDE_DIR}/modules/juce_audio_utils/juce_audio_utils.cpp
    ${JUCE_INCLUDE_DIR}/modules/juce_core/juce_core.cpp
    ${JUCE_INCLUDE_DIR}/modules/juce_cryptography/juce_cryptography.cpp
    ${JUCE_INCLUDE_DIR}/modules/juce_data_structures/juce_data_structures.cpp
    ${JUCE_INCLUDE_DIR}/modules/juce_events/juce_events.cpp
    ${JUCE_INCLUDE_DIR}/modules/juce_graphics/juce_graphics.cpp
    ${JUCE_INCLUDE_DIR}/modules/juce_gui_basics/juce_gui_basics.cpp
    ${JUCE_INCLUDE_DIR}/modules/juce_gui_extra/juce_gui_extra.cpp
    ${JUCE_INCLUDE_DIR}/modules/juce_audio_plugin_client/VST/juce_VST_Wrapper.cpp
  )
endif(${SYSTEM_IS_MACOSX})

# Disable warnings for external source
disable_warnings_list("${INSTANTSONICVIEW_JUCE_SRC}")

# Include all subdirectories plugin source files
add_subdirectory(vst)

source_group("juce_externals" FILES ${INSTANTSONICVIEW_JUCE_SRC})
source_group("instantsonicview" FILES ${INSTANTSONICVIEW_SRC} ${INSTANTSONICVIEW_HDR})
source_group("instantsonicview_implementation" FILES ${INSTANTSONICVIEW_IMPLEMENTATION_SRC} ${INSTANTSONICVIEW_IMPLEMENTATION_HDR})
source_group("vst_specifics" FILES ${INSTANTSONICVIEW_PLUGIN_VST_SRC} ${INSTANTSONICVIEW_PLUGIN_VST_HDR})

add_library(instantsonicview_vst SHARED
  ${INSTANTSONICVIEW_JUCE_SRC}
  ${INSTANTSONICVIEW_SRC}
  ${INSTANTSONICVIEW_HDR}
  ${INSTANTSONICVIEW_IMPLEMENTATION_SRC}
  ${INSTANTSONICVIEW_IMPLEMENTATION_HDR}
  ${INSTANTSONICVIEW_PLUGIN_VST_SRC}
  ${INSTANTSONICVIEW_PLUGIN_VST_HDR}
)


# Specific Mac stuff
if (${SYSTEM_IS_MACOSX})
  # Bundle stuff
  set_target_properties(instantsonicview_vst PROPERTIES
    BUNDLE TRUE
    BUNDLE_EXTENSION vst
    XCODE_ATTRIBUTE_WRAPPER_EXTENSION vst
    XCODE_ATTRIBUTE_MACH_O_TYPE mh_bundle
    XCODE_ATTRIBUTE_INFOPLIST_FILE ${CMAKE_CURRENT_BINARY_DIR}/bundle/Info.plist
    MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_BINARY_DIR}/bundle/Info.plist
    RESOURCE ${ARGN}
  )

  # Linker: set framework to use
  add_linker_flags(instantsonicview_vst "-framework Accelerate")

  set(CMAKE_OSX_DEPLOYEMENT_TARGET 10.5)
  set(CMAKE_XCODE_ATTRIBUTE_GCC_VERSION com.apple.compilers.llvm.clang.1_0)

endif (${SYSTEM_IS_MACOSX})

target_link_libraries(instantsonicview_vst
                      chartreuse_lib
                      instantsonicview_lib)

set_target_mt(instantsonicview_vst)
