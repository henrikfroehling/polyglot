### Documentation

##### The project consists of three subprojects.

- polyglot: A shared library for multi language static analysis.
- polyglot-driver: A console application for running analysis.
- polyglot-sandbox: A UI application for conveniently testing the library.

#### Common Required Prerequisites

- CMake Version >= 3.16.0
- C++ Compiler with support for C++20-Standard

#### Optional Prerequisites

- Qt 6 Version >= 6.0.2 (required for the polyglot-sandbox project)

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


#### Options

Usage: `-DVARIABLE_NAME=VALUE`

- `CMAKE_BUILD_TYPE`: Defaults to `DEBUG`. Set this to `RELEASE` to build a release version.
- `BUILD_LIBRARY_DRIVER`: Defaults to `OFF`. Set this to `ON` (`-DBUILD_LIBRARY_DRIVER=ON`) to build the polyglot-driver console application additionaly.
- `BUILD_LIBRARY_SANDBOX`: Defaults to `OFF`. Set this to `ON` (`-DBUILD_LIBRARY_SANDBOX=ON`) to build the polyglot-sandbox application additionaly.
