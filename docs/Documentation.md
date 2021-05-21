### Documentation

##### The project consists of three subprojects.

- polyglot: A shared library for multi language static analysis.
- polyglot-driver: A console application for running analysis.
- polyglot-sandbox: A UI application for conveniently testing the library.

#### Common Required Prerequisites

- CMake Version >= 3.16.0
- C++ Compiler with support for C++20-Standard

#### Optional Prerequisites

- Qt 5 (required for the polyglot-sandbox project)

#### How to build the library from command line

The recommended way to build and develop the project is to use an IDE, e.g. Visual Studio 2019, Visual Studio Code, Qt Creator or CLion.

But you can also build the project from command line.

1. Open a shell. Your development tools must be reachable from this shell through the PATH environment variable.
2. Create a build directory. Building the project in the source directory is not supported. cd into this directory.
```
mkdir build
cd build
```
3. Run CMake within the previous created built directory with the path to the root of your polyglot source tree.
```
cmake path/to/polyglot/source/root
```
CMake will use default values for all build parameters. See the [Options](https://github.com/henrikfroehling/polyglot/blob/develop/docs/Documentation.md#options) section for a list of build parameters that you can modify.

4. After CMake has finished running, start the build from the build directory.
```
cmake --build .
```

The built binaries are written to `your-build-directory/output`.

##### *For building and developing the polyglot-sandbox project the usage of Qt Creator is recommend.*
---
#### Options

Usage: `-DVARIABLE_NAME=VALUE`

- `CMAKE_BUILD_TYPE`: Defaults to `DEBUG`. Set this to `RELEASE` to build a release version.
- `BUILD_LIBRARY_DRIVER`: Defaults to `OFF`. Set this to `ON` (`-DBUILD_LIBRARY_DRIVER=ON`) to build the polyglot-driver console application additionaly.
- `BUILD_LIBRARY_SANDBOX`: Defaults to `OFF`. Set this to `ON` (`-DBUILD_LIBRARY_SANDBOX=ON`) to build the polyglot-sandbox application additionaly.


#### Example CMake configurations for Visual Studio 2019 (`CMakeSettings.json`)

```json
{
  "configurations": [
    {
      "name": "Driver-x86-MSVC-Debug",
      "generator": "Ninja",
      "configurationType": "Debug",
      "buildRoot": "${projectDir}\\vsbuild\\${name}",
      "installRoot": "${projectDir}\\install\\${name}",
      "cmakeCommandArgs": "-DBUILD_LIBRARY_DRIVER=ON",
      "buildCommandArgs": "",
      "addressSanitizerEnabled": true,
      "enableMicrosoftCodeAnalysis": true,
      "ctestCommandArgs": "",
      "inheritEnvironments": [ "msvc_x86" ]
    },
    {
      "name": "Driver-x64-MSVC-Debug",
      "generator": "Ninja",
      "configurationType": "Debug",
      "buildRoot": "${projectDir}\\vsbuild\\${name}",
      "installRoot": "${projectDir}\\install\\${name}",
      "cmakeCommandArgs": "-DBUILD_LIBRARY_DRIVER=ON",
      "buildCommandArgs": "",
      "addressSanitizerEnabled": true,
      "enableMicrosoftCodeAnalysis": true,
      "ctestCommandArgs": "",
      "inheritEnvironments": [ "msvc_x64_x64" ]
    },
    {
      "name": "Driver-x86-MSVC-Release",
      "generator": "Ninja",
      "configurationType": "Release",
      "buildRoot": "${projectDir}\\vsbuild\\${name}",
      "installRoot": "${projectDir}\\install\\${name}",
      "cmakeCommandArgs": "-DBUILD_LIBRARY_DRIVER=ON",
      "buildCommandArgs": "",
      "enableMicrosoftCodeAnalysis": true,
      "ctestCommandArgs": "",
      "inheritEnvironments": [ "msvc_x86" ]
    },
    {
      "name": "Driver-x64-MSVC-Release",
      "generator": "Ninja",
      "configurationType": "Release",
      "buildRoot": "${projectDir}\\vsbuild\\${name}",
      "installRoot": "${projectDir}\\install\\${name}",
      "cmakeCommandArgs": "-DBUILD_LIBRARY_DRIVER=ON",
      "buildCommandArgs": "",
      "enableMicrosoftCodeAnalysis": true,
      "ctestCommandArgs": "",
      "inheritEnvironments": [ "msvc_x64_x64" ]
    },
    {
      "name": "Driver-x64-WSL-Clang-Debug",
      "generator": "Ninja",
      "configurationType": "Debug",
      "buildRoot": "${projectDir}\\vsbuild\\${name}",
      "installRoot": "${projectDir}\\install\\${name}",
      "cmakeExecutable": "cmake",
      "cmakeCommandArgs": "-DBUILD_LIBRARY_DRIVER=ON",
      "buildCommandArgs": "",
      "ctestCommandArgs": "",
      "inheritEnvironments": [ "linux_clang_x64" ],
      "wslPath": "${defaultWSLPath}"
    },
    {
      "name": "Driver-x64-WSL-Clang-Release",
      "generator": "Ninja",
      "configurationType": "Release",
      "buildRoot": "${projectDir}\\vsbuild\\${name}",
      "installRoot": "${projectDir}\\install\\${name}",
      "cmakeExecutable": "cmake",
      "cmakeCommandArgs": "-DBUILD_LIBRARY_DRIVER=ON",
      "buildCommandArgs": "",
      "ctestCommandArgs": "",
      "inheritEnvironments": [ "linux_clang_x64" ],
      "wslPath": "${defaultWSLPath}"
    },
    {
      "name": "Library-only-x86-MSVC-Debug",
      "generator": "Ninja",
      "configurationType": "Debug",
      "buildRoot": "${projectDir}\\vsbuild\\${name}",
      "installRoot": "${projectDir}\\install\\${name}",
      "buildCommandArgs": "",
      "ctestCommandArgs": "",
      "inheritEnvironments": [ "msvc_x86" ],
      "addressSanitizerEnabled": true
    },
    {
      "name": "Library-only-x64-MSVC-Debug",
      "generator": "Ninja",
      "configurationType": "Debug",
      "buildRoot": "${projectDir}\\vsbuild\\${name}",
      "installRoot": "${projectDir}\\install\\${name}",
      "buildCommandArgs": "",
      "ctestCommandArgs": "",
      "inheritEnvironments": [ "msvc_x64_x64" ],
      "addressSanitizerEnabled": true
    },
    {
      "name": "Library-only-x86-MSVC-Release",
      "generator": "Ninja",
      "configurationType": "Release",
      "buildRoot": "${projectDir}\\vsbuild\\${name}",
      "installRoot": "${projectDir}\\install\\${name}",
      "buildCommandArgs": "",
      "ctestCommandArgs": "",
      "inheritEnvironments": [ "msvc_x86" ],
      "addressSanitizerEnabled": true
    },
    {
      "name": "Library-only-x64-MSVC-Release",
      "generator": "Ninja",
      "configurationType": "Release",
      "buildRoot": "${projectDir}\\vsbuild\\${name}",
      "installRoot": "${projectDir}\\install\\${name}",
      "buildCommandArgs": "",
      "ctestCommandArgs": "",
      "inheritEnvironments": [ "msvc_x64_x64" ]
    },
    {
      "name": "Driver-x86-WSL-Debug",
      "generator": "Ninja",
      "configurationType": "Debug",
      "buildRoot": "${projectDir}\\vsbuild\\${name}",
      "installRoot": "${projectDir}\\install\\${name}",
      "cmakeExecutable": "cmake",
      "cmakeCommandArgs": "-DBUILD_LIBRARY_DRIVER=ON",
      "buildCommandArgs": "",
      "ctestCommandArgs": "",
      "inheritEnvironments": [ "linux_x86" ],
      "wslPath": "${defaultWSLPath}"
    },
    {
      "name": "Driver-x86-WSL-Release",
      "generator": "Ninja",
      "configurationType": "Release",
      "buildRoot": "${projectDir}\\vsbuild\\${name}",
      "installRoot": "${projectDir}\\install\\${name}",
      "cmakeExecutable": "cmake",
      "cmakeCommandArgs": "-DBUILD_LIBRARY_DRIVER=ON",
      "buildCommandArgs": "",
      "ctestCommandArgs": "",
      "inheritEnvironments": [ "linux_x86" ],
      "wslPath": "${defaultWSLPath}"
    },
    {
      "name": "Library-only-x64-WSL-Clang-Debug",
      "generator": "Ninja",
      "configurationType": "Debug",
      "buildRoot": "${projectDir}\\vsbuild\\${name}",
      "installRoot": "${projectDir}\\install\\${name}",
      "cmakeExecutable": "cmake",
      "buildCommandArgs": "",
      "ctestCommandArgs": "",
      "inheritEnvironments": [ "linux_clang_x64" ],
      "wslPath": "${defaultWSLPath}"
    },
    {
      "name": "Library-only-x64-WSL-Clang-Release",
      "generator": "Ninja",
      "configurationType": "Release",
      "buildRoot": "${projectDir}\\vsbuild\\${name}",
      "installRoot": "${projectDir}\\install\\${name}",
      "cmakeExecutable": "cmake",
      "buildCommandArgs": "",
      "ctestCommandArgs": "",
      "inheritEnvironments": [ "linux_clang_x64" ],
      "wslPath": "${defaultWSLPath}"
    },
    {
      "name": "Library-only-x86-WSL-Debug",
      "generator": "Ninja",
      "configurationType": "Debug",
      "buildRoot": "${projectDir}\\vsbuild\\${name}",
      "installRoot": "${projectDir}\\install\\${name}",
      "cmakeExecutable": "cmake",
      "buildCommandArgs": "",
      "ctestCommandArgs": "",
      "inheritEnvironments": [ "linux_x86" ],
      "wslPath": "${defaultWSLPath}"
    },
    {
      "name": "Library-only-x86-WSL-Release",
      "generator": "Ninja",
      "configurationType": "Release",
      "buildRoot": "${projectDir}\\vsbuild\\${name}",
      "installRoot": "${projectDir}\\install\\${name}",
      "cmakeExecutable": "cmake",
      "buildCommandArgs": "",
      "ctestCommandArgs": "",
      "inheritEnvironments": [ "linux_x86" ],
      "wslPath": "${defaultWSLPath}",
      "variables": []
    }
  ]
}
```
