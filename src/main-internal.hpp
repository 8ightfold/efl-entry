//===- main-internal.hpp --------------------------------------------===//
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
//  This file provides the definitions required for main-entry.
//
//===----------------------------------------------------------------===//

#ifdef EFLI_MAIN_INTERNAL_HPP
#  error "main-internal.hpp" can only be included once.
#else
#  define EFLI_MAIN_INTERNAL_HPP
#endif

#include <efl/Entry.hpp>
#include <efl/Config.hpp>

#ifdef _MSC_VER
#  if __has_include(<wchar.h>)
#    include <wchar.h>
#    define EFLI_ENTRY_WIDE_ 1
#  endif
#endif // MSVC Check

#if EFLI_SHARED_ == 1
#  error The main entry point cannot be used in shared libraries.
#endif // Shared Check

#if EFLI_ENTRY_STRONG_ == 0
#  if defined(COMPILER_GNU) || defined(COMPILER_LLVM)
#    define EFLI_WEAK_ __attribute__((weak))
#  endif
#endif // Strong Entry

#ifndef EFLI_WEAK_
#  define EFLI_WEAK_
#  define EFLI_NOWEAK_
#endif

namespace {
    char* efl_win_utf8conv(wchar_t* ws) {
#   ifdef EFLI_ENTRY_WIDE_
        int len = wcslen(ws);
        int to_alloc = WideCharToMultiByte(
          CP_UTF8, 0, ws, len + 1, NULL, 0, NULL, NULL);
        if(to_alloc <= 0) return nullptr;

        char* data = new char[to_alloc];
        if(WideCharToMultiByte(
          CP_UTF8, 0, ws, len + 1, data, to_alloc, NULL, NULL) <= 0) {
            delete[] data;
            return nullptr;
        }
        
        return data;
#   else
        (void) ws;
        UNREACHABLE();
#   endif
    }

    namespace efl::entry {
        constexpr const char entrypoint_str_[] = 
            STRINGIFY(EFL_ENTRYPOINT);
    } // namespace efl::entry
} // namespace `anonymous`