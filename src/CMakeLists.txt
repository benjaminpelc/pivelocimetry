cmake_minimum_required(VERSION 2.8)
project(bppiv)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR
	"${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
	set(warnings "-Wall -Wextra -Werror")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${warnings} -std=c++14 -Ofast -m64 -march=native -fdiagnostics-color=auto -g -fdiagnostics-show-template-tree")
	# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${warnings} -std=c++14 -Ofast -m64 -march=native -fdiagnostics-color=auto -g -fdiagnostics-show-template-tree -fsanitize=undefined,integer")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
	set(warnings "/W4 /WX /EHsc")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /O2 ")
endif()

# Define sources and executable name
set(EXECUTABLE_NAME "bppiv")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../bin/")
# find_package(OpenCV REQUIRED)

# find_package(SFML 2 REQUIRED system window graphics)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-3.0)

add_executable(${EXECUTABLE_NAME} 
		../lib/Clap.cpp
		find_peaks.cpp
		utils.cpp
		Disp.cpp
		DoPiv.cpp
		DoPost.cpp
		Grid.cpp
		IntMap.cpp
		GtkImage.cpp
		PivClap.cpp
		PivOptions.cpp
		PivPoint.cpp
		SubPix.cpp
		PivVector.cpp
		XCorr2.cpp
		main.cpp
		PivViewGtk.cpp
	)
include_directories(${GTKMM_INCLUDE_DIRS})
link_directories(${GTKMM_LIBRARY_DIRS})
target_link_libraries(${EXECUTABLE_NAME} ${GTKMM_LIBRARIES})
