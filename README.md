# <NAME>Particle Image Velocimetry

## Introduction
A C++ PIV implementation utilizing the Gonzalez [1, 2] normalized spatial cross-correlation algorithm. The cross-correlation algorithm implementation can be found in 'src/XCorr2.cpp'. 

N.B. Top level class and function/method comments are written in the header files stored in the 'include' directory. These comments are not repeated in the implementation files to avoid divergence. 

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
CMake is required to build the project. 

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
After compiling and from the 'build' directory run `./piv`. For help on command line options run `./piv --help`. To run with all default settings and the default image pair and print the calculated vectors to STDOUT run `./piv -p`. 

## References
[1] Huang, H. and Dabiri, D. and Gharib, M. (1997) *On errors of digital particle image velocimetry*. Measurement Science and Technology, 8 (12). pp. 1427-1440. ISSN 0957-0233.

[2] Gonzalez, R. C. and Woods, R. E. (2001). *Digital Image Processing*. Addison-Wesley Longman Publishing Co., Inc.
