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

add_subdirectory(UnitTests)
