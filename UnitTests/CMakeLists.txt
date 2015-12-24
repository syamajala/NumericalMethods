enable_testing()

macro (add_executable _name)
  _add_executable(${ARGV})
  if(TARGET ${_name})
    target_link_libraries(${_name} ${ARMADILLO_LIBRARIES} ${ANN_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
    set_target_properties(${_name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY bin)
  endif()

  add_test(NAME ${_name} COMMAND ${CMAKE_COMMAND}
    -Dtest_cmd=${CMAKE_BINARY_DIR}/UnitTests/bin/${_name}
    -Doutput_blessed=${CMAKE_SOURCE_DIR}/UnitTests/output/${_name}.output
    -Doutput_test=${CMAKE_BINARY_DIR}/UnitTests/Testing/${_name}.output
    -P ${CMAKE_SOURCE_DIR}/UnitTests/run_test.cmake
    )
endmacro()


add_executable(NonlinearSystems NonlinearSystems.cpp)
add_executable(Interpolation Interpolation.cpp)
add_executable(InterpolationSystem InterpolationSystem.cpp)
add_executable(Differentiation Differentiation.cpp)
add_executable(Integration Integration.cpp)
add_executable(IVP IVP.cpp)
add_executable(IVPSystem IVPSystem.cpp)


# add_test(NAME NonlinearSystems COMMAND ${CMAKE_COMMAND}
#   -Dtest_cmd=${CMAKE_BINARY_DIR}/UnitTests/bin/NonlinearSystems
#   -Doutput_blessed=${CMAKE_SOURCE_DIR}/UnitTests/output/NonlinearSystems.output
#   -Doutput_test=${CMAKE_BINARY_DIR}/UnitTests/Testing/NonlinearSystems.output
#   -P ${CMAKE_SOURCE_DIR}/UnitTests/run_test.cmake
#   )
