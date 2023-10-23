add_library(__efl_entry_api INTERFACE)
target_include_directories(__efl_entry_api INTERFACE include)
target_link_libraries(__efl_entry_api INTERFACE efl::config)

add_library(__efl_entry_shared STATIC src/shared-entry.cpp)
target_compile_definitions(__efl_entry_shared PUBLIC EFLI_SHARED_=1)
target_link_libraries(__efl_entry_shared PUBLIC __efl_entry_api)

add_library(__efl_entry_main STATIC src/main-entry.cpp)
target_compile_definitions(__efl_entry_main PUBLIC EFLI_SHARED_=0)
target_link_libraries(__efl_entry_main PUBLIC __efl_entry_api)

if(__EFL_VALID_ENTRY)
  target_compile_definitions(__efl_entry_main PUBLIC 
    EFL_ENTRYPOINT=${EFL_ENTRY} EFLI_ENTRY_GLOBAL_=1)
endif()

if(EFL_ENTRY_STRONG)
  target_compile_definitions(__efl_entry_main PRIVATE
    EFLI_ENTRY_STRONG_=1)
endif()