cmake_minimum_required(VERSION 2.8)
project(bppiv)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" )
	set(warnings "-Wall -Wextra -Werror")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${warnings} -std=c++14 -Ofast -m64 -march=native")

elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${warnings} -std=c++14 -Ofast -m64 -march=native -fdiagnostics-color=auto -g -fdiagnostics-show-template-tree")
	# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${warnings} -std=c++14 -01 -m64 -march=native -fdiagnostics-color=auto -g -fdiagnostics-show-template-tree -fsanitize=address")

elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
	set(warnings "/W4 /WX /EHsc")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /O2 ")

endif()

# Define sources and executable name
set(EXECUTABLE_NAME "bppiv")

# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "./bin/")

include_directories(include)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-3.0)

set(SOURCES
		./lib/Clap.cpp
		./src/find_peaks.cpp
		./src/utils.cpp
		./src/Disp.cpp
		./src/DoPiv.cpp
		./src/DoPost.cpp
		./src/Grid.cpp
		./src/IntMap.cpp
		./src/GtkImage.cpp
		./src/PivClap.cpp
		./src/PivOptions.cpp
		./src/PivPoint.cpp
		./src/SubPix.cpp
		./src/PivVector.cpp
		./src/XCorr2.cpp
		./src/main.cpp
		./src/PivViewGtk.cpp
		./src/myarea.cpp
		./src/MyAreaD.cpp
	)

add_executable(${EXECUTABLE_NAME} ${SOURCES} )

include_directories(${GTKMM_INCLUDE_DIRS})
link_directories(${GTKMM_LIBRARY_DIRS})

target_link_libraries(${EXECUTABLE_NAME} ${GTKMM_LIBRARIES} -lpthread)
