cmake_minimum_required(VERSION 3.5)
project(SGE)

include(CMakeModules/sge_debug_info.cmake)

option(PACKAGE_MANAGER "Default project package manager, default: NONE" NONE)
option(CMAKE_INSTALL_PREFIX "Defines to path in which SGE framework should be installed, default: NONE" NONE)

set(MASTER_BUILD_TYPES "Debug Release RelWithDebInfo MinSizeRel")
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
	set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build -- release is default. Other: ${MASTER_BUILD_TYPES}.")
	message(STATUS "Setting default CMake build type: ${CMAKE_BUILD_TYPE}")
else()
	set(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE} CACHE STRING "Choose the type of build -- release is default. Other: ${MASTER_BUILD_TYPES}.")
	message(STATUS "Provided CMake build type: ${CMAKE_BUILD_TYPE}")
endif()
string(REPLACE " " ";" MASTER_BUILD_TYPES_AVAILABLE ${MASTER_BUILD_TYPES})
set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS ${MASTER_BUILD_TYPES_AVAILABLE})

if (NOT PACKAGE_MANAGER)
	message(WARNING "Option PACKAGE_MANAGER not passed, setting: NONE")
	set(PACKAGE_MANAGER "NONE")
endif()
set(PKG "")
if (${PACKAGE_MANAGER} STREQUAL "Conan" OR ${PACKAGE_MANAGER} STREQUAL "conan" OR ${PACKAGE_MANAGER} STREQUAL "CONAN")
	set(PKG "CONAN")
elseif(${PACKAGE_MANAGER} STREQUAL "None" OR ${PACKAGE_MANAGER} STREQUAL "none" OR ${PACKAGE_MANAGER} STREQUAL "NONE")
	set(PKG "NONE")
elseif(${PACKAGE_MANAGER} STREQUAL "Local" OR ${PACKAGE_MANAGER} STREQUAL "local" OR ${PACKAGE_MANAGER} STREQUAL "LOCAL")
	set(PKG "LOCAL")

	if (NOT SETUP_BUILD_DIR)
		message(WARNING "Option SETUP_BUILD_DIR has not been provided. Using default value: Setup/build")
		set(SETUP_BUILD_DIR "Setup/build")
	endif()
else()
	message(WARNING "PACKAGE_MANAGER defined error: ${PACKAGE_MANAGER} ${PKG}")
	return()
endif()

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/$<CONFIG>")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/$<CONFIG>")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH ON)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_STANDARD 14)

if (NOT CMAKE_BUILD_TYPE)
    message(STATUS "No build type selected -- default is Debug")
    set(CMAKE_BUILD_TYPE "Debug")
endif()

message(STATUS "BUILD TYPE: ${CMAKE_BUILD_TYPE}")

if (BUILD_SHARED_LIBS AND WIN32)
	message(STATUS "BUILD_SHARED_LIBS is ON. Adding compiler defintion.")
	add_definitions(-DSGE_SHARED)
endif()

if (UNIX)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")

    if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
        message(STATUS "Linux")

        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fext-numeric-literals -pthread -ldl")
        set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -fext-numeric-literals -pthread -ldl")
    
	elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
        message(STATUS "Darwin")

        set(CMAKE_MACOSX_RPATH OFF)
	endif()

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive")

    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
    set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -O3")

	set(CMAKE_C_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")
    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
    set(CMAKE_C_FLAGS_RELWITHDEBINFO "${CMAKE_C_FLAGS_RELWITHDEBINFO} -O3")

elseif(WIN32)
    message(STATUS "WINDOWS")

    if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
        message (STATUS "MSVC ${MSVC_VERSION}v")

        set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
		set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Od /W2")
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2")
        set(CMAKE_CXX_FLAGS_RELWITHDEBINFO  "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} /O2")

        set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} /MP")
		set(CMAKE_C_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Od /W2")
        set(CMAKE_C_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2")
        set(CMAKE_C_FLAGS_RELWITHDEBINFO "${CMAKE_C_FLAGS_RELWITHDEBINFO} /O2")

        set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT SGE-ZombieGame)
        link_directories("${CMAKE_CURRENT_BINARY_DIR}/lib")

        include_directories("${CMAKE_CURRENT_BINARY_DIR}/SimpleGameEngine/Logic_lib")
        include_directories("${CMAKE_CURRENT_BINARY_DIR}/SimpleGameEngine/Utils_lib")
        include_directories("${CMAKE_CURRENT_BINARY_DIR}/SimpleGameEngine/ThirdParty_Librarys/Box2D")

    else()
		## TODO: Add support for MinGW on Windows platform
        status(FATAL_ERROR "Other compiler than MSVC in curentley not supported for Windows build!")
        return()
    endif()
endif()


if (PKG STREQUAL "CONAN")
	message(STATUS "Using PACKAGE_MANAGER: CONAN")

	include(${CMAKE_CURRENT_SOURCE_DIR}/conanbuildinfo.cmake)
	conan_basic_setup()

	include(CMakeModules/sge_common_find.cmake)
elseif(PKG STREQUAL "LOCAL")
	message(STATUS "Using PACKAGE_MANAGER: LOCAL")
	message(STATUS "SETUP_BUILD_DIR: ${SETUP_BUILD_DIR}")

	include(CMakeModules/sge_setup.cmake)
else()
	message(STATUS "Using PACKAGE_MANAGER: NONE")
	message(STATUS "No ROOT for libs will be set up")
	message(STATUS "CMAKE_TOOLCHAIN_FILE: ${CMAKE_TOOLCHAIN_FILE}")

	include(CMakeModules/sge_common_find.cmake)
endif()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMakeModules")

## Boost:
find_package(Boost COMPONENTS date_time program_options system filesystem REQUIRED)
if(NOT Boost_FOUND)
	message(Error "Boost not found")
else()
	include_directories(${Boost_INCLUDE_DIRS})
	link_directories(${Boost_LIBRARY_DIRS})
endif()

# SDL:
find_package(SDL2 REQUIRED)
if (NOT SDL2_FOUND)
	message(Error "SDL2 not found")
else()
	include_directories("${SDL2_INCLUDE_DIR}")
	include_directories("${SDL2_INCLUDE_DIR}/SDL2")
	link_directories("${SDL2_DIR}/lib")
	add_definitions(${SDL2_DEFINITIONS})
endif()

## OpenGL:
find_package(OpenGL REQUIRED)
if(NOT OpenGL_FOUND)
        message(Error "OpenGL not found")
else()
	include_directories(${OpenGL_INCLUDE_DIRS})
	link_directories(${OpenGL_LIBRARY_DIRS})
	add_definitions(${OpenGL_DEFINITIONS})
endif()

include(CMakeModules/sge_status.cmake)

set(SGE_DIR "SimpleGameEngine")

add_subdirectory(${SGE_DIR})

## install step
install(DIRECTORY "${SGE_DIR}/Action_lib/Action"
		DESTINATION "${CMAKE_INSTALL_PREFIX}/include"
		FILES_MATCHING
		PATTERN "*.h*")
install(DIRECTORY "${SGE_DIR}/IO_lib/"
		DESTINATION "${CMAKE_INSTALL_PREFIX}/include/IO"
		FILES_MATCHING
		PATTERN "*.h*")
install(DIRECTORY "${SGE_DIR}/Level_lib/"
		DESTINATION "${CMAKE_INSTALL_PREFIX}/include/Level"
		FILES_MATCHING
		PATTERN "*.h*")
install(DIRECTORY "${SGE_DIR}/Logic_lib/Logic/"
		DESTINATION "${CMAKE_INSTALL_PREFIX}/include/Logic"
		FILES_MATCHING
		PATTERN "*.h*")
install(DIRECTORY "${SGE_DIR}/Object_lib/"
		DESTINATION "${CMAKE_INSTALL_PREFIX}/include/Object"
		FILES_MATCHING
		PATTERN "*.h*")
install(DIRECTORY "${SGE_DIR}/Game_lib/"
		DESTINATION "${CMAKE_INSTALL_PREFIX}/include/Game"
		FILES_MATCHING
		PATTERN "*.h*")
install(DIRECTORY "${SGE_DIR}/Renderer_lib/"
		DESTINATION "${CMAKE_INSTALL_PREFIX}/include/Renderer"
		FILES_MATCHING
		PATTERN "*.h*")
install(DIRECTORY "${SGE_DIR}/Scene_lib/Scene"
		DESTINATION "${CMAKE_INSTALL_PREFIX}/include"
		FILES_MATCHING
		PATTERN "*.h*")
install(DIRECTORY "${SGE_DIR}/ThirdParty_Librarys/PicoPNG"
		DESTINATION "${CMAKE_INSTALL_PREFIX}/include"
		FILES_MATCHING
		PATTERN "*.h*")
install(DIRECTORY "${SGE_DIR}/ThirdParty_Librarys/Box2D/Box2D"
		DESTINATION "${CMAKE_INSTALL_PREFIX}/include"
		FILES_MATCHING
		PATTERN "*.h*")
install(DIRECTORY "${SGE_DIR}/Utils_lib/"
		DESTINATION "${CMAKE_INSTALL_PREFIX}/include/Utils"
		FILES_MATCHING
		PATTERN "*.h*")