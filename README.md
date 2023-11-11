# efl-entry
This is a library made for creating custom "entry points".
Instead of dealing with ``main``, you can provide a function with the
correct signature to act as the entry.

### Overview

To get started, all you need is something like:

```cpp
#include <efl/Entry.hpp>

int cppmain(const efl::ProgramArgs& args) {
    ...
    return 0;
}
```

Then in your ``CMakeLists.txt``:

```cmake
add_subdirectory(efl-entry)
...
target_link_libraries(your-exe efl::entry-main)
```

## C++ Usage

``<efl/Entry.hpp>`` defines a few things:

```cpp
#define EFL_ENTRY_VERSION "..."
#define EFL_ENTRYPOINT ...

namespace efl::entry {
    struct ProgramArgSpan {
        ProgramArgSpan(char* argv[]);
        ProgramArgSpan(char** beg, char** end);
        ProgramArgSpan(int argc, char* argv[]);
    
        int size() const noexcept;
        char** begin() const noexcept;
        char** end() const noexcept;

        char* operator[](std::size_t n);

        ...
    };
} // namespace efl::entry

namespace efl {
    struct ProgramArgs {
        Path program_path;
        entry::ProgramArgSpan& args;
    };
} // namespace efl
```

- ``EFL_ENTRYPOINT``: the name of the entry function.
    This defaults to ``cppmain``.
- ``efl::ProgramArgs``: a wrapper type around the program arguments. 
    ``program_path`` is ``argv[0]``, and ``args`` are the arguments ``argv[1:]``. ``args`` is both iterable and random-access,
    and its elements are mutable 
    (even when the object is ``const``).

### Signature

The required signature for the entry point is as follows:

```cpp
int EFL_ENTRYPOINT(const efl::ProgramArgs& args);
```

This is the signature used internally, and must be followed.
The function must be global with external linkage.

By default, ``efl::entry`` attempts to use weak linkage
for the internal declaration. This means you will not get
linker errors, and instead get a runtime error.
This will only occur on GNU/llvm compilers.

## CMake Usage

``efl::entry`` defines three targets:

- ``efl::entry``: Includes ``<efl/Entry.hpp>``
- ``efl::entry-main``: Generates the ``main`` function
    to be used by the main executable.
- ``efl::entry-shared``: Generates a cross platform
    entry point for .dll/.so files.

### Custom Entry Functions

Defining a custom entry point is simple:
just call ``Efl_TargetAddentry`` on your target.

This will define ``EFL_ENTRYPOINT`` as ``my_main``:

```cmake
add_subdirectory(efl-entry)
...
Efl_TargetAddentry(tgt VISIBILITY my_main)
```

You can also use names that would be impossible in
C++ by setting ``EFL_PERMISSIVE_NAMING`` to ``ON``.
This will replace spaces and dashes with underscores.

This will define ``EFL_ENTRYPOINT`` as ``entry_func``:

```cmake
set(EFL_PERMISSIVE_NAMING ON)
add_subdirectory(efl-entry)
...
Efl_TargetAddentry(tgt VISIBILITY "entry-func")
```

### Entry Function Linkage

As previously stated, the entry point is declared
with weak linkage by default. To disable this, 
set ``EFL_ENTRY_STRONG`` to ``ON``. 
This will force errors to occur during link time.