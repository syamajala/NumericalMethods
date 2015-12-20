cmake_minimum_required (VERSION 2.8)
project (NumericalMethods)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(Armadillo REQUIRED)
include_directories(${ARMADILLO_INCLUDE_DIRS})

include(FindPackageHandleStandardArgs)
find_path(ANN_INCLUDE_DIR ANN/ANN.h)
find_library(ANN_LIBRARY ANN)

find_package_handle_standard_args(ANN DEFAULT_MSG ANN_LIBRARY ANN_INCLUDE_DIR)

if(ANN_FOUND)
  set(ANN_INCLUDE_DIRS ${ANN_INCLUDE_DIR})
  set(ANN_LIBRARIES ${ANN_LIBRARY})
  include_directories(${ANN_INCLUDE_DIRS})
endif()

include_directories("${PROJECT_SOURCE_DIR}")

macro (add_executable _name)
  _add_executable(${ARGV})
  if(TARGET ${_name})
    target_link_libraries(${_name} ${ARMADILLO_LIBRARIES} ${ANN_LIBRARIES})
    set_target_properties(${_name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY bin)
  endif()
endmacro()

set(CMAKE_BUILD_TYPE Debug)

add_subdirectory(UnitTests)
add_subdirectory(Problems)
