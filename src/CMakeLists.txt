cmake_minimum_required(VERSION 2.8)
project(bppiv)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR
	"${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
	set(warnings "-Wall -Wextra -Werror")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -O2 -march=native ")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
	set(warnings "/W4 /WX /EHsc")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /O2 ")
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../bin/")
find_package(OpenCV REQUIRED)
add_executable(bppiv 
		main.cpp
		ocv_image.cpp
		int_map.cpp
		pivoptions.cpp
	)
target_link_libraries(bppiv ${OpenCV_LIBS})
