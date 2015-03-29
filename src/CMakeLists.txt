cmake_minimum_required(VERSION 2.8)
project(bppiv)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR
	"${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
	set(warnings "-Wall -Wextra -Werror")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${warnings} -std=c++14 -O2 -march=native -fdiagnostics-color=auto")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
	set(warnings "/W4 /WX /EHsc")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /O2 ")
endif()

# Define sources and executable name
set(EXECUTABLE_NAME "bppiv")

# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../bin/")
find_package(OpenCV REQUIRED)
find_package(SFML 2 REQUIRED system window graphics)
add_executable(${EXECUTABLE_NAME} 
		main.cpp
		OcvImage.cpp
		Ccf.cpp
		XCorr2.cpp
		Grid.cpp
		IntMap.cpp
		../lib/Clap.cpp
		PivOptions.cpp
		SubPix.cpp

		DoPost.cpp
	)
target_link_libraries(${EXECUTABLE_NAME} ${OpenCV_LIBS} ${SFML_LIBRARIES})
