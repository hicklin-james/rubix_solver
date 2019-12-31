# cmake version to be used
cmake_minimum_required( VERSION 3.3 )

# cmake functions
include( CMakeFunctions.cmake )

# project name
project( rubix_solver )

# flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

include_directories( include )
# logging headers
include_directories( external/spdlog/include )

enum2str_generate(
  PATH       "generated/"
  CLASS_NAME "enum2Str"
  NAMESPACE  "EnumUtils"
  FUNC_NAME  "toStr"
  INCLUDES   "util.h"
  ENUMS      "FaceOrientation" "FaceColor"
)

include_directories( generated )
 
file(GLOB SOURCES "src/*.cpp")
file(GLOB GEN_SOURCES "generated/*.cpp")
 
add_executable(solver ${SOURCES} ${GEN_SOURCES})
target_link_libraries(solver ${CMAKE_SOURCE_DIR}/external/spdlog/build/libspdlog.a)