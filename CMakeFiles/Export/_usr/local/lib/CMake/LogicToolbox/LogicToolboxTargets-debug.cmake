#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "logictoolbox" for configuration "Debug"
set_property(TARGET logictoolbox APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(logictoolbox PROPERTIES
  IMPORTED_LOCATION_DEBUG "/usr/local/lib/liblogictoolbox.so"
  IMPORTED_SONAME_DEBUG "liblogictoolbox.so"
  )

list(APPEND _IMPORT_CHECK_TARGETS logictoolbox )
list(APPEND _IMPORT_CHECK_FILES_FOR_logictoolbox "/usr/local/lib/liblogictoolbox.so" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
