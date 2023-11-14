//===- EntryShared.cpp ----------------------------------------------===//
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
//  This file implements a shared library entry point.
//
//===----------------------------------------------------------------===//

#include <efl/Config.hpp>

#ifdef PLATFORM_WINDOWS
#  include <WinDef.h>
#  include <process.h>

namespace efl::entry {
  inline HINSTANCE current_module_ = nullptr;
} // namespace efl::entry

BOOL WINAPI DllMain(HINSTANCE mod, DWORD reason, LPVOID) {
  if(reason == DLL_PROCESS_ATTACH)
    efl::entry::current_module_ = mod;
  return TRUE;
}

#endif // Windows Check