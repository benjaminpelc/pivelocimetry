cmake_minimum_required(VERSION 2.8)
project(OCVIClass)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR
	"${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
	set(warnings "-Wall -Wextra -Werror")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
	set(warnings "/W4 /WX /EHsc")
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../bin/")
find_package(OpenCV REQUIRED)
add_executable(OCVIClass main.cpp ocv_image.cpp int_map.cpp)
target_link_libraries(OCVIClass ${OpenCV_LIBS})
