# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Questions_and_answers_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Questions_and_answers_autogen.dir\\ParseCache.txt"
  "Questions_and_answers_autogen"
  )
endif()
