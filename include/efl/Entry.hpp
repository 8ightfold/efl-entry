//===- efl/Entry.hpp ------------------------------------------------===//
//
// Copyright (C) 2023 Eightfold
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
//     limitations under the License.
//
//===----------------------------------------------------------------===//
//
//  This file contains definition required for interfacing
//  with custom entry points.
//
//===----------------------------------------------------------------===//

#ifndef EFL_ENTRY_HPP
#define EFL_ENTRY_HPP

#include <filesystem>
#include <efl/Config.hpp>

#if !CPPVER_LEAST(17)
#  error efl::entry requires at least C++17. \
    Required: std::filesystem, std::string_view
#endif // C++17 Check

#ifndef EFL_ENTRYPOINT
#  define EFL_ENTRYPOINT cppmain
#endif

#ifndef EFLI_ENTRY_STRONG_
#  define EFLI_ENTRY_STRONG_ 0
#endif

//=== Inclusions ===//
namespace efl {
  namespace fs = std::filesystem;
  using Path = fs::path;
} // namespace efl

//=== Implementation ===//
namespace efl::entry {
  struct ProgramArgSpan {
    ProgramArgSpan(char* argv[]) : argv_(argv) {
      while(argv[argc_]) ++argc_;
    }

    ProgramArgSpan(char** beg_, char** end_) : argv_(beg_) {
      argc_ = static_cast<int>(end_ - beg_);
    }

    ProgramArgSpan(int argc, char* argv[]) 
     : argc_(argc), argv_(argv) { }
  
  public:
    int size() CNOEXCEPT { return argc_; }
    char** begin() CNOEXCEPT { return argv_; }
    char** end() CNOEXCEPT { return argv_ + argc_; }

    char* operator[](std::size_t n) CNOEXCEPT {
      if(n < argc_) LIKELY return argv_[n];
      else UNLIKELY return nullptr;
    }

  private:
    int argc_ = 0;
    mutable char** argv_;
  };
} // namespace efl::entry

//=== Definitions ===//
namespace efl {
  struct ProgramArgs {
    Path program_path;
    entry::ProgramArgSpan& args;
  };
} // namespace efl

#endif // EFL_ENTRY_HPP