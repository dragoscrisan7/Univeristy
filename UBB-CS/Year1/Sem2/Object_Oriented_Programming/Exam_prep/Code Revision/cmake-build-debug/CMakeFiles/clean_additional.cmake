# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Code_Revision_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Code_Revision_autogen.dir\\ParseCache.txt"
  "Code_Revision_autogen"
  )
endif()
