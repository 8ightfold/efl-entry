//===- main-entry.cpp -----------------------------------------------===//
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
//  This file implements a custom standalone entry point.
//
//===----------------------------------------------------------------===//

#include <cstdio>
#include "main-internal.hpp"

using GPath = ::efl::Path;
using GProgramArgs = ::efl::ProgramArgs;
using GProgramArgSpan = ::efl::entry::ProgramArgSpan;

int EFLI_WEAK_ EFL_ENTRYPOINT(const GProgramArgs& pargs);

namespace {
    int invoke_entry_(const GProgramArgs& pargs) {
#   ifndef EFLI_NOWEAK_
        if(EFL_ENTRYPOINT == nullptr) {
            std::fprintf(stderr, 
                "[FATAL] entry-point `%s` is undefined.\n",
                efl::entry::entrypoint_str_);
            fflush(stderr);
            return -1;
        }
#   endif // Weak Linkage Check
        return EFL_ENTRYPOINT(pargs);
    }

    int main_(int argc, char* argv[]) {
        GPath program_path = argc ? *argv : "";
        GProgramArgSpan args { argv + 1, argv + argc };
        const GProgramArgs pargs { program_path, args };
        return invoke_entry_(pargs);
    }
} // namespace `anonymous`


#ifndef EFLI_ENTRY_WIDE_
  int main(int c, char* v[]) { 
      return main_(c, v); 
  }
#else
#  include <vector>

  int wmain(int c, wchar_t* wv[]) {
      std::vector<char*> v;
      v.reserve(c)
      if(c > 0) 
        for(wchar_t** wargs = wv; *wv; ++wv) {
          char* arg = efl_win_utf8conv(*wv);
          if(arg) v.push_back(arg);
      }
      v.push_back(nullptr);
      return main_(c, v.data());
  }
#endif