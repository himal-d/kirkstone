#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "native-ical-glib-src-generator" for configuration ""
set_property(TARGET native-ical-glib-src-generator APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(native-ical-glib-src-generator PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/libexec/libical/ical-glib-src-generator"
  )

list(APPEND _IMPORT_CHECK_TARGETS native-ical-glib-src-generator )
list(APPEND _IMPORT_CHECK_FILES_FOR_native-ical-glib-src-generator "${_IMPORT_PREFIX}/libexec/libical/ical-glib-src-generator" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
