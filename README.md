# tray

**Basic offline CPU ray-tracer using (only) C++20**

`tray` is a "tutorial project", structured such that it progresses linearly and is easy to follow along, but is also fully runnable at any tag / commit (on `main`). The wiki has chapters corresponding to a tag / branch each, which can be checked out as a "snapshot" to follow along / experiment with.

## Requriements

1. CMake 3.18+
1. C++20 compiler and standard library / runtime

## Development

The project is developed on Linux using VSCode with the CMake Tools extension, though it is designed to be agnostic to individual workflows. Regardless of OS / IDE / editor of choice, make sure the debugger works once the build has been setup, that you can set breakpoints, watch/change variables, etc.

### Linux

If using VSCode and CMake Tools, just open the root directory, select `CMake: Configure` from the command palette, pick a preset (`default` or `ninja-ubsan` are best for debugging), and get started. Use `CMake: Build` and `CMake: Debug` / `Ctrl + F5` subsequently as needed.

For other IDEs / workflows, use CMake to configure a preset and/or a custom a build directory and then use that.

### Windows

The most straightforward approach would be to use Visual Studio in CMake mode: install the appropriate tools, then simply open the root folder in the IDE, it should detect the CMake script and switch to that mode. Configure, build, debug as usual.

Alternatively, use CMake to generate a Visual Studio solution offline, then open and use that. You'll have to regenerate the solution every time the CMake script changes - since VS would be unaware of its existence.

Using VSCode etc with Ninja / clang++ is also an option: follow the same steps as in the [Linux](#Linux) section.

### CLI

Use CMake:

```
cmake -S . --list-presets         # list all configure presets
cmake -S . --preset=<preset>      # configure using desired configure preset
cmake --build --list-presets      # list all build presets
cmake --build --preset=<preset>   # build the desired build preset
```

