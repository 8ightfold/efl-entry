if(DEFINED EFL_ENTRYPOINT)
  if(DEFINED EFL_ENTRY AND 
   NOT EFL_ENTRY STREQUAL EFL_ENTRYPOINT)
    message(WARNING 
      "EFL_ENTRY and EFL_ENTRYPOINT are both defined "
      "and are not equal, EFL_ENTRY will take precedence.")
  else()
    set(EFL_ENTRY "${EFL_ENTRYPOINT}")
  endif()
endif()

if(DEFINED EFL_ENTRY AND 
 NOT EFL_ENTRY STREQUAL "efl::default")
  string(REGEX MATCHALL "[^ ]+" __EFL_PARSED_ENTRY "${EFL_ENTRY}")
  if(EFL_PERMISSIVE_NAMING)
    string(REGEX REPLACE "[;-]" "_" __EFL_PARSED_ENTRY "${__EFL_PARSED_ENTRY}")
    set(EFL_ENTRY "${__EFL_PARSED_ENTRY}")
  endif()

  string(REGEX MATCH "^[_a-zA-Z]+$" __EFL_PARSED_ENTRY_CHECK "${__EFL_PARSED_ENTRY}")
  if(__EFL_PARSED_ENTRY_CHECK STREQUAL "")
    set(__EFL_VALID_ENTRY OFF)
    message(SEND_ERROR "[efl::entry] Invalid entry-point `${EFL_ENTRY}`")
  else()
    set(__EFL_VALID_ENTRY ON)
  endif()
else()
  set(EFL_ENTRY "cppmain")
  set(__EFL_VALID_ENTRY ON)
endif()

if(__EFL_VALID_ENTRY AND NOT PROJECT_IS_TOP_LEVEL)
  set(EFL_ENTRY "${EFL_ENTRY}" PARENT_SCOPE)
elseif(NOT __EFL_VALID_ENTRY)
  set(EFL_ENTRY "[invalid-entry]")
endif()