# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "Bachelor_Thesis_autogen"
  "CMakeFiles\\Bachelor_Thesis_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Bachelor_Thesis_autogen.dir\\ParseCache.txt"
  )
endif()
