# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\pregatire_test_qt_1_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\pregatire_test_qt_1_autogen.dir\\ParseCache.txt"
  "pregatire_test_qt_1_autogen"
  )
endif()
