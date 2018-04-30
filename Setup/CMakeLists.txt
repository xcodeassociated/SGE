cmake_minimum_required(VERSION 3.5)
project(SGE-ZombieGame-setup)

set(INSTALL_DEPENDENCIES_DIR "${CMAKE_SOURCE_DIR}/build" CACHE STRING "" FORCE)

option(PROCESSOR_COUNT "Set processor count, default 4" "4")

set(PROCESSOR_COUNT 4)

message(STATUS "INSTALL_DEPENDENCIES_DIR: ${INSTALL_DEPENDENCIES_DIR}")
message(STATUS "CPUs: ${PROCESSOR_COUNT}")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

message(STATUS "CMAKE_CURRENT_BINARY_DIR: ${CMAKE_CURRENT_BINARY_DIR}")
message(STATUS "CMAKE_LIBRARY_OUTPUT_DIRECTORY: ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
message(STATUS "CMAKE_RUNTIME_OUTPUT_DIRECTORY: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")

set(BUILD_SHARED_LIBS ON)

include("${CMAKE_ROOT}/Modules/ExternalProject.cmake")

include(ExternalBoost.cmake)
include(ExternalGLM.cmake)

if(NOT ${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	if (NOT ${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
		include(ExternalSDL2.cmake)
	else()
		message(WARNING  "On macOS please manually download and extract `SDL2.framework` from `https://www.libsdl.org/download-2.0.php`  into `/Library/Frameworks` folder.")
	endif()

    include(ExternalGLEW.cmake)
else()
    message(WARNING "On Linux please install SDL2 and GLEW manually -- there are too many dependencies on this system, use following commands: ")
    message(WARNING "$ sudo apt-get install freeglut3 freeglut3-dev libglew1.5 libglew1.5-dev libglu1-mesa libglu1-mesa-dev libgl1-mesa-glx libgl1-mesa-dev")
    message(WARNING "$ sudo apt-get install libsdl2-dev")
endif()
