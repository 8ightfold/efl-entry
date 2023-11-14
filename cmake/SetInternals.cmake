add_library(__efl_entry_api INTERFACE)
target_include_directories(__efl_entry_api INTERFACE include)
target_link_libraries(__efl_entry_api INTERFACE efl::config)
target_compile_definitions(__efl_entry_api INTERFACE
  EFL_ENTRY_VERSION=${PROJECT_VERSION})

add_library(__efl_entry_shared STATIC src/EntryShared.cpp)
target_compile_definitions(__efl_entry_shared PUBLIC EFLI_SHARED_=1)
target_link_libraries(__efl_entry_shared PUBLIC __efl_entry_api)

add_library(__efl_entry_main STATIC src/EntryMain.cpp)
target_compile_definitions(__efl_entry_main PUBLIC EFLI_SHARED_=0)
target_link_libraries(__efl_entry_main PUBLIC __efl_entry_api)

set(ENV{__EFL_ENTRY_SRC} ${PROJECT_SOURCE_DIR}/src)

if(EFL_ENTRY_STRONG)
  target_compile_definitions(__efl_entry_main PRIVATE
    EFLI_ENTRY_STRONG_=1)
endif()