# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.1

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ben/Dropbox/Development/C++/BPPIV/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ben/Dropbox/Development/C++/BPPIV/src

# Include any dependencies generated for this target.
include CMakeFiles/OCVIClass.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/OCVIClass.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/OCVIClass.dir/flags.make

CMakeFiles/OCVIClass.dir/main.cpp.o: CMakeFiles/OCVIClass.dir/flags.make
CMakeFiles/OCVIClass.dir/main.cpp.o: main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ben/Dropbox/Development/C++/BPPIV/src/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/OCVIClass.dir/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/OCVIClass.dir/main.cpp.o -c /home/ben/Dropbox/Development/C++/BPPIV/src/main.cpp

CMakeFiles/OCVIClass.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/OCVIClass.dir/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ben/Dropbox/Development/C++/BPPIV/src/main.cpp > CMakeFiles/OCVIClass.dir/main.cpp.i

CMakeFiles/OCVIClass.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/OCVIClass.dir/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ben/Dropbox/Development/C++/BPPIV/src/main.cpp -o CMakeFiles/OCVIClass.dir/main.cpp.s

CMakeFiles/OCVIClass.dir/main.cpp.o.requires:
.PHONY : CMakeFiles/OCVIClass.dir/main.cpp.o.requires

CMakeFiles/OCVIClass.dir/main.cpp.o.provides: CMakeFiles/OCVIClass.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/OCVIClass.dir/build.make CMakeFiles/OCVIClass.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/OCVIClass.dir/main.cpp.o.provides

CMakeFiles/OCVIClass.dir/main.cpp.o.provides.build: CMakeFiles/OCVIClass.dir/main.cpp.o

CMakeFiles/OCVIClass.dir/ocv_image.cpp.o: CMakeFiles/OCVIClass.dir/flags.make
CMakeFiles/OCVIClass.dir/ocv_image.cpp.o: ocv_image.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ben/Dropbox/Development/C++/BPPIV/src/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/OCVIClass.dir/ocv_image.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/OCVIClass.dir/ocv_image.cpp.o -c /home/ben/Dropbox/Development/C++/BPPIV/src/ocv_image.cpp

CMakeFiles/OCVIClass.dir/ocv_image.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/OCVIClass.dir/ocv_image.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ben/Dropbox/Development/C++/BPPIV/src/ocv_image.cpp > CMakeFiles/OCVIClass.dir/ocv_image.cpp.i

CMakeFiles/OCVIClass.dir/ocv_image.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/OCVIClass.dir/ocv_image.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ben/Dropbox/Development/C++/BPPIV/src/ocv_image.cpp -o CMakeFiles/OCVIClass.dir/ocv_image.cpp.s

CMakeFiles/OCVIClass.dir/ocv_image.cpp.o.requires:
.PHONY : CMakeFiles/OCVIClass.dir/ocv_image.cpp.o.requires

CMakeFiles/OCVIClass.dir/ocv_image.cpp.o.provides: CMakeFiles/OCVIClass.dir/ocv_image.cpp.o.requires
	$(MAKE) -f CMakeFiles/OCVIClass.dir/build.make CMakeFiles/OCVIClass.dir/ocv_image.cpp.o.provides.build
.PHONY : CMakeFiles/OCVIClass.dir/ocv_image.cpp.o.provides

CMakeFiles/OCVIClass.dir/ocv_image.cpp.o.provides.build: CMakeFiles/OCVIClass.dir/ocv_image.cpp.o

CMakeFiles/OCVIClass.dir/int_map.cpp.o: CMakeFiles/OCVIClass.dir/flags.make
CMakeFiles/OCVIClass.dir/int_map.cpp.o: int_map.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ben/Dropbox/Development/C++/BPPIV/src/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/OCVIClass.dir/int_map.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/OCVIClass.dir/int_map.cpp.o -c /home/ben/Dropbox/Development/C++/BPPIV/src/int_map.cpp

CMakeFiles/OCVIClass.dir/int_map.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/OCVIClass.dir/int_map.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ben/Dropbox/Development/C++/BPPIV/src/int_map.cpp > CMakeFiles/OCVIClass.dir/int_map.cpp.i

CMakeFiles/OCVIClass.dir/int_map.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/OCVIClass.dir/int_map.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ben/Dropbox/Development/C++/BPPIV/src/int_map.cpp -o CMakeFiles/OCVIClass.dir/int_map.cpp.s

CMakeFiles/OCVIClass.dir/int_map.cpp.o.requires:
.PHONY : CMakeFiles/OCVIClass.dir/int_map.cpp.o.requires

CMakeFiles/OCVIClass.dir/int_map.cpp.o.provides: CMakeFiles/OCVIClass.dir/int_map.cpp.o.requires
	$(MAKE) -f CMakeFiles/OCVIClass.dir/build.make CMakeFiles/OCVIClass.dir/int_map.cpp.o.provides.build
.PHONY : CMakeFiles/OCVIClass.dir/int_map.cpp.o.provides

CMakeFiles/OCVIClass.dir/int_map.cpp.o.provides.build: CMakeFiles/OCVIClass.dir/int_map.cpp.o

# Object files for target OCVIClass
OCVIClass_OBJECTS = \
"CMakeFiles/OCVIClass.dir/main.cpp.o" \
"CMakeFiles/OCVIClass.dir/ocv_image.cpp.o" \
"CMakeFiles/OCVIClass.dir/int_map.cpp.o"

# External object files for target OCVIClass
OCVIClass_EXTERNAL_OBJECTS =

/home/ben/Dropbox/Development/C++/BPPIV/bin/OCVIClass: CMakeFiles/OCVIClass.dir/main.cpp.o
/home/ben/Dropbox/Development/C++/BPPIV/bin/OCVIClass: CMakeFiles/OCVIClass.dir/ocv_image.cpp.o
/home/ben/Dropbox/Development/C++/BPPIV/bin/OCVIClass: CMakeFiles/OCVIClass.dir/int_map.cpp.o
/home/ben/Dropbox/Development/C++/BPPIV/bin/OCVIClass: CMakeFiles/OCVIClass.dir/build.make
/home/ben/Dropbox/Development/C++/BPPIV/bin/OCVIClass: /usr/lib/libopencv_videostab.so.2.4.10
/home/ben/Dropbox/Development/C++/BPPIV/bin/OCVIClass: /usr/lib/libopencv_ts.a
/home/ben/Dropbox/Development/C++/BPPIV/bin/OCVIClass: /usr/lib/libopencv_superres.so.2.4.10
/home/ben/Dropbox/Development/C++/BPPIV/bin/OCVIClass: /usr/lib/libopencv_stitching.so.2.4.10
/home/ben/Dropbox/Development/C++/BPPIV/bin/OCVIClass: /usr/lib/libopencv_contrib.so.2.4.10
/home/ben/Dropbox/Development/C++/BPPIV/bin/OCVIClass: /lib64/libGLU.so
/home/ben/Dropbox/Development/C++/BPPIV/bin/OCVIClass: /lib64/libGL.so
/home/ben/Dropbox/Development/C++/BPPIV/bin/OCVIClass: /lib64/libSM.so
/home/ben/Dropbox/Development/C++/BPPIV/bin/OCVIClass: /lib64/libICE.so
/home/ben/Dropbox/Development/C++/BPPIV/bin/OCVIClass: /lib64/libX11.so
/home/ben/Dropbox/Development/C++/BPPIV/bin/OCVIClass: /lib64/libXext.so
/home/ben/Dropbox/Development/C++/BPPIV/bin/OCVIClass: /usr/lib/libopencv_nonfree.so.2.4.10
/home/ben/Dropbox/Development/C++/BPPIV/bin/OCVIClass: /usr/lib/libopencv_ocl.so.2.4.10
/home/ben/Dropbox/Development/C++/BPPIV/bin/OCVIClass: /usr/lib/libopencv_gpu.so.2.4.10
/home/ben/Dropbox/Development/C++/BPPIV/bin/OCVIClass: /usr/lib/libopencv_photo.so.2.4.10
/home/ben/Dropbox/Development/C++/BPPIV/bin/OCVIClass: /usr/lib/libopencv_objdetect.so.2.4.10
/home/ben/Dropbox/Development/C++/BPPIV/bin/OCVIClass: /usr/lib/libopencv_legacy.so.2.4.10
/home/ben/Dropbox/Development/C++/BPPIV/bin/OCVIClass: /usr/lib/libopencv_video.so.2.4.10
/home/ben/Dropbox/Development/C++/BPPIV/bin/OCVIClass: /usr/lib/libopencv_ml.so.2.4.10
/home/ben/Dropbox/Development/C++/BPPIV/bin/OCVIClass: /usr/lib/libopencv_calib3d.so.2.4.10
/home/ben/Dropbox/Development/C++/BPPIV/bin/OCVIClass: /usr/lib/libopencv_features2d.so.2.4.10
/home/ben/Dropbox/Development/C++/BPPIV/bin/OCVIClass: /usr/lib/libopencv_highgui.so.2.4.10
/home/ben/Dropbox/Development/C++/BPPIV/bin/OCVIClass: /usr/lib/libopencv_imgproc.so.2.4.10
/home/ben/Dropbox/Development/C++/BPPIV/bin/OCVIClass: /usr/lib/libopencv_flann.so.2.4.10
/home/ben/Dropbox/Development/C++/BPPIV/bin/OCVIClass: /usr/lib/libopencv_core.so.2.4.10
/home/ben/Dropbox/Development/C++/BPPIV/bin/OCVIClass: CMakeFiles/OCVIClass.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable /home/ben/Dropbox/Development/C++/BPPIV/bin/OCVIClass"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/OCVIClass.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/OCVIClass.dir/build: /home/ben/Dropbox/Development/C++/BPPIV/bin/OCVIClass
.PHONY : CMakeFiles/OCVIClass.dir/build

CMakeFiles/OCVIClass.dir/requires: CMakeFiles/OCVIClass.dir/main.cpp.o.requires
CMakeFiles/OCVIClass.dir/requires: CMakeFiles/OCVIClass.dir/ocv_image.cpp.o.requires
CMakeFiles/OCVIClass.dir/requires: CMakeFiles/OCVIClass.dir/int_map.cpp.o.requires
.PHONY : CMakeFiles/OCVIClass.dir/requires

CMakeFiles/OCVIClass.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/OCVIClass.dir/cmake_clean.cmake
.PHONY : CMakeFiles/OCVIClass.dir/clean

CMakeFiles/OCVIClass.dir/depend:
	cd /home/ben/Dropbox/Development/C++/BPPIV/src && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ben/Dropbox/Development/C++/BPPIV/src /home/ben/Dropbox/Development/C++/BPPIV/src /home/ben/Dropbox/Development/C++/BPPIV/src /home/ben/Dropbox/Development/C++/BPPIV/src /home/ben/Dropbox/Development/C++/BPPIV/src/CMakeFiles/OCVIClass.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/OCVIClass.dir/depend
