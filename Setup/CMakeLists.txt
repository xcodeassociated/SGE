cmake_minimum_required(VERSION 3.5)
project(SGE-ZombieGame-setup)

message(WARNING "Using `vcpkg` or `conan` is more durable way to configure SGE dependencies than Setup project.")
message(WARNING "Microsoft vcpkg is cross platform now! It is recommened to use vckpg or conan package manager instead!")

option(INSTALL_DEPENDENCIES_DIR "Directory in which the dependencies libs will be installed")
if (NOT INSTALL_DEPENDENCIES_DIR)
	message(WARNING "INSTALL_DEPENDENCIES_DIR has not been given, setting default value: ${CMAKE_SOURCE_DIR}/build")
	set(INSTALL_DEPENDENCIES_DIR "${CMAKE_SOURCE_DIR}/build")
endif()

option(PROCESSOR_COUNT "Set processor count, default 4" 4)
if (NOT PROCESSOR_COUNT)
	message(WARNING "PROCESSOR_COUNT has not been given, setting default value: 4. This variable is used for building boost libs.")
	set(PROCESSOR_COUNT 4)
endif()

message(STATUS "INSTALL_DEPENDENCIES_DIR: ${INSTALL_DEPENDENCIES_DIR}")
message(STATUS "CPUs: ${PROCESSOR_COUNT}")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${INSTALL_DEPENDENCIES_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${INSTALL_DEPENDENCIES_DIR}")

message(STATUS "CMAKE_CURRENT_BINARY_DIR: ${CMAKE_CURRENT_BINARY_DIR}")
message(STATUS "CMAKE_LIBRARY_OUTPUT_DIRECTORY: ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
message(STATUS "CMAKE_RUNTIME_OUTPUT_DIRECTORY: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")

include("${CMAKE_ROOT}/Modules/ExternalProject.cmake")

## BOOST and GLM for all the platforms
include(ExternalBoost.cmake)
include(ExternalGLM.cmake)

if(NOT ${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	if (NOT ${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
		## WINDOWS
		message(WARNING "On Windows platform please install GLEW and SDL2 manually. These libs has too many system dependencies to install them via Setup project.")
		message(WARNING "The following packages will be installed:")
		message(WARNING "	BOOST")
		message(WARNING "	GLM")
	else()
		## macOS
		message(WARNING "On macOS please manually download and extract `SDL2.framework` from `https://www.libsdl.org/download-2.0.php`  into `/Library/Frameworks` folder.")
		message(WARNING "The following packages will be installed:")
		message(WARNING "	BOOST")
		message(WARNING "	GLM")
		message(WARNING "	GLEW")
		
		include(ExternalGLEW.cmake)
	endif()
else()
	## LINUX
    message(WARNING "On Linux please install SDL2 and GLEW manually -- there are too many dependencies on this system, use following commands: ")
    message(WARNING "$ sudo apt-get install freeglut3 freeglut3-dev libglew1.5 libglew1.5-dev libglu1-mesa libglu1-mesa-dev libgl1-mesa-glx libgl1-mesa-dev")
    message(WARNING "$ sudo apt-get install libsdl2-dev")
endif()