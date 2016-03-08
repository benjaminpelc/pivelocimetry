# <NAME>Particle Image Velocimetry

## Introduction
A C++ PIV implementation utilizing the Gonzalez [1, 2] normalized cross-correlation algorithm.

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

## Build Instructions
### Dependencies
Make sure Gtkmm-3 and TCLAP are installed on your system before attempting to compile. In future versions these libraries will be included within this repository. 

### Build
From the base directory:
```bash
mkdir build
cd build
cmake ..
make
```

## Usage Instructions
After compiling and from the 'build' directory run `./piv`. For help on command line options run `./piv --help`.

## References
[1] Huang, H. and Dabiri, D. and Gharib, M. (1997) *On errors of digital particle image velocimetry*. Measurement Science and Technology, 8 (12). pp. 1427-1440. ISSN 0957-0233.

[2] Gonzalez, R. C. and Woods, R. E. (2001). *Digital Image Processing*. Addison-Wesley Longman Publishing Co., Inc.
