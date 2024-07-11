# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Quiz_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Quiz_autogen.dir\\ParseCache.txt"
  "Quiz_autogen"
  )
endif()
