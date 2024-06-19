# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Star_Catalogue_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Star_Catalogue_autogen.dir\\ParseCache.txt"
  "Star_Catalogue_autogen"
  )
endif()
