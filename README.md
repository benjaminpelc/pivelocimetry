# <NAME>Particle Image Velocimetry

## Contents
1. Introduction
2. Build Instructions
3. Usage Instructions
4. References

## Repository Directory Structure
<pre>
├── build
|     binaries and CMakeFiles
|
├── config
|     configuration files containing PIV analysis
|     options.
|
├── img
|     source images to do PIV analysis on
|
├── include
|     C++ header files
|
├── lib
|     external libraries
|
├── prof
|     profiling files
|
├── src
|     C++ source files
|
└── tests
      C++ source test files
</pre>

## Introduction
A C++ PIV implementation utilizing the Gonzalez [1, 2] normalized cross-correlation algorithm.

## Build Instructions
From the base directory:
```bash
cd build
cmake ..
make
```

## Usage Instructions
After compiling and from the 'build' directory run `./piv`

## References
[1] Huang, H. and Dabiri, D. and Gharib, M. (1997) *On errors of digital particle image velocimetry*. Measurement Science and Technology, 8 (12). pp. 1427-1440. ISSN 0957-0233.

[2] Gonzalez, R. C. and Woods, R. E. (2001). *Digital Image Processing*. Addison-Wesley Longman Publishing Co., Inc.
