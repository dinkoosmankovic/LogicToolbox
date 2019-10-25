

set(command "/usr/bin/cmake;-DCMAKE_BUILD_TYPE=Debug;-Dgtest_force_shared_crt=ON;-GUnix Makefiles;/home/alma/Documents/LogicToolbox/ThirdParty/src/googletest")
execute_process(
  COMMAND ${command}
  RESULT_VARIABLE result
  OUTPUT_FILE "/home/alma/Documents/LogicToolbox/ThirdParty/src/googletest-stamp/googletest-configure-out.log"
  ERROR_FILE "/home/alma/Documents/LogicToolbox/ThirdParty/src/googletest-stamp/googletest-configure-err.log"
  )
if(result)
  set(msg "Command failed: ${result}\n")
  foreach(arg IN LISTS command)
    set(msg "${msg} '${arg}'")
  endforeach()
  set(msg "${msg}\nSee also\n  /home/alma/Documents/LogicToolbox/ThirdParty/src/googletest-stamp/googletest-configure-*.log")
  message(FATAL_ERROR "${msg}")
else()
  set(msg "googletest configure command succeeded.  See also /home/alma/Documents/LogicToolbox/ThirdParty/src/googletest-stamp/googletest-configure-*.log")
  message(STATUS "${msg}")
endif()
