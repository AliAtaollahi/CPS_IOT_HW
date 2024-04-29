# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\MonitoritngSystem_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\MonitoritngSystem_autogen.dir\\ParseCache.txt"
  "MonitoritngSystem_autogen"
  )
endif()
