cmake_minimum_required(VERSION 3.13)
include_guard(DIRECTORY)

project(
  efl-entry
  VERSION 2.0.1
  LANGUAGES CXX
)

option(EFL_PERMISSIVE_NAMING "Replaces spaces and dashes with underscores." OFF)
option(EFL_ENTRY_STRONG "Forces the application to use a strong entry symbol." OFF)

include(EflGetModules)
include(cmake/SetEntryPoint.cmake)

Efl_Getmodules(efl::config)

message("[efl::entry] permissive-naming: ${EFL_PERMISSIVE_NAMING}")
message("[efl::entry] strong-entry: ${EFL_ENTRY_STRONG}")

include(cmake/SetInternals.cmake)

add_library(efl::entry ALIAS __efl_entry_api)
add_library(efl::entry-main ALIAS __efl_entry_main)
add_library(efl::entry-shared ALIAS __efl_entry_shared)