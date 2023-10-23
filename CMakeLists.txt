cmake_minimum_required(VERSION 3.13)
include_guard(DIRECTORY)

project(
  efl-entry
  VERSION 1.0.0
  LANGUAGES CXX
)

option(EFL_PERMISSIVE_NAMING "Replaces spaces and dashes with underscores." OFF)
option(EFL_ENTRY_STRONG "Forces the application to use a strong entry symbol." OFF)

include(cmake/SetEntryPoint.cmake)
add_subdirectory(submodules/efl-config)

message("[efl::entry] entry-point: ${EFL_ENTRY}")
message("[efl::entry] strong-entry: ${EFL_ENTRY_STRONG}")

include(cmake/SetInternals.cmake)

##=== API ===##
add_library(efl::entry ALIAS __efl_entry_api)
add_library(efl::entry-main ALIAS __efl_entry_main)
add_library(efl::entry-shared ALIAS __efl_entry_shared)