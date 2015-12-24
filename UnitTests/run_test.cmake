if( NOT test_cmd )
  message( FATAL_ERROR "Variable test_cmd not defined" )
endif( NOT test_cmd )
# output_blessed contains the name of the "blessed" output file
if( NOT output_blessed )
    message( FATAL_ERROR "Variable output_blessed not defined" )
endif( NOT output_blessed )
# output_test contains the name of the output file the test_cmd will produce
if( NOT output_test )
   message( FATAL_ERROR "Variable output_test not defined" )
endif( NOT output_test )

execute_process(
  COMMAND ${test_cmd}
  OUTPUT_FILE ${output_test}
  )

execute_process (
  COMMAND ${CMAKE_COMMAND} -E compare_files ${output_blessed} ${output_test}
  RESULT_VARIABLE test_failure
  )

if( test_failure )
    message( SEND_ERROR "${output_test} does not match ${output_blessed}" )
endif( test_failure )
