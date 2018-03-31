cmake_minimum_required(VERSION 3.5)

## Project name 
project(SGE-ZombieGame)

## Output directory for all compiled objects
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/$<CONFIG>")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/$<CONFIG>")
set(BUILD_SHARED_LIBS ON)

## include conan cmake file
include(${CMAKE_CURRENT_SOURCE_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

message(STATUS "CMAKE_VERSION: ${CMAKE_VERSION}")
message(STATUS "CMAKE_SYSTEM:  ${CMAKE_SYSTEM}")
message(STATUS "CMAKE_COMMAND: ${CMAKE_COMMAND}")
message(STATUS "CMAKE_C_COMPILER: ${CMAKE_C_COMPILER}")
message(STATUS "CMAKE_CXX_COMPILER: ${CMAKE_CXX_COMPILER}")
message(STATUS "CMAKE_AR: ${CMAKE_AR}")
message(STATUS "CMAKE_RANLIB: ${CMAKE_RANLIB}")
message(STATUS "BUILD_SHARED_LIBS on: ${BUILD_SHARED_LIBS}")
message(STATUS "CMAKE_ROOT: ${CMAKE_ROOT}")
message(STATUS "CMAKE_CURRENT_LIST_FILE: ${CMAKE_CURRENT_LIST_FILE}")
message(STATUS "Source DIR: ${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "Build DIR: ${CMAKE_CURRENT_BINARY_DIR}")
message(STATUS "Binary DIR: ${CMAKE_BINARY_DIR}")
message(STATUS "Library Output DIR: ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
message(STATUS "CMAKE_RUNTIME_OUTPUT_DIRECTORY: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
message(STATUS "EXECUTABLE_OUTPUT_PATH: ${EXECUTABLE_OUTPUT_PATH}")

set(CMAKE_VERBOSE_MAKEFILE on)
set(CMAKE_CXX_STANDARD 14)

## Setting default build type is no has been selected
if (NOT CMAKE_BUILD_TYPE)
    message(STATUS "No build type selected -- default is Release")
    set(CMAKE_BUILD_TYPE "Release")
endif()

message(STATUS "BUILD TYPE: ${CMAKE_BUILD_TYPE}")

if (UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic")
    if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
        message(STATUS "Linux")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fext-numeric-literals")

    elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
        message(STATUS "Darwin")

    endif()

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive")

    if (CMAKE_BUILD_TYPE MATCHES "Debug")
        message(STATUS "DEBUG MODE -- UNIX")
        ## ..
    elseif (CMAKE_BUILD_TYPE MATCHES "Release")
        message(STATUS "RELEASE MODE -- UNIX")
        ## ..
    endif()

    SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")
    SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

elseif(WIN32)
    message(STATUS "WIN32")

        if (MSVC)
            message (STATUS "MSVC")

            ## Use all cores during the compilation
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")

            ## These mess up release builds. Use Only for Debug
            ##SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} /NODEFAULTLIB:msvcrt.lib" )
            ##SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} /NODEFAULTLIB:MSVCRT" )
            ##SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} /NODEFAULTLIB:msvcrt.lib" )

            ## Set Project
            set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT SGE-ZombieGame)
            ## Force exports without adding macros in sources.
            set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS 1)
            ## TODO: WIN32 compiler flags here!!!
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W2")
            ## Remove that for Box2D
            ## set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Za")
            ## Adds export libraries directory
            link_directories("${CMAKE_CURRENT_BINARY_DIR}/lib")
            ## Add exports
            include_directories("${CMAKE_CURRENT_BINARY_DIR}/SimpleGameEngine/Logic_lib")
            include_directories("${CMAKE_CURRENT_BINARY_DIR}/SimpleGameEngine/Utils_lib")
            include_directories("${CMAKE_CURRENT_BINARY_DIR}/SimpleGameEngine/ThirdParty_Librarys/Box2D")

            if (CMAKE_BUILD_TYPE MATCHES "Debug")
                message(STATUS "DEBUG MODE -- WIN MSVC")
                ## ..
            elseif (CMAKE_BUILD_TYPE MATCHES "Release")
                message(STATUS "RELEASE MODE -- WIN MSVC")
                ## ..
            endif()

            SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Od")
            SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2")

        elseif(MINGW)
            status(FATAL_ERROR "MinGW in curentley not supported for Windows build!")
            return()
        endif()

endif()

## FINDING MODULES
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMakeModules")

## Boost:
find_package(Boost COMPONENTS date_time program_options system filesystem REQUIRED)
if(NOT Boost_FOUND)
	message(Error "Boost not found")
else()
    include_directories(${Boost_INCLUDE_DIRS})

    message(STATUS "Boost Found!")
    message(STATUS "Boost version: ${Boost_VERSION}")
    message(STATUS "Boost include: ${Boost_INCLUDE_DIRS}")
    message(STATUS "Boost libs: ${Boost_LIBRARY_DIRS}")
endif()

## SDL:
find_package(SDL2 REQUIRED)
if (NOT SDL2_FOUND)
	message(Error "SDL2 not found")
else()
	include_directories(${SDL2_INCLUDE_DIR})
	link_directories(${SDL2_INCLUDE_DIR})
    add_definitions(${SDL2_DEFINITIONS})

endif()


## GLM:
find_package(GLM REQUIRED)
if(NOT GLM_FOUND)
    message(Error "GLM not found")
else()
    include_directories(${GLM_INCLUDE_DIRS})
    link_directories(${GLM_LIBRARY_DIRS})
    add_definitions(${GLM_DEFINITIONS})
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

## GLEW:
find_package(GLEW REQUIRED)
if(NOT GLEW_FOUND)
        message(Error "GLEW not found")
else()
	include_directories(${GLEW_INCLUDE_DIRS})
	link_directories(${GLEW_LIBRARY_DIRS})
	add_definitions(${GLEW_DEFINITIONS})

    ## TODO: Remove this work-around - on Unix find_package(GLEW REQUIRED) uses static lib
    if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
        set(GLEW_LIBRARIES "libGLEW.so")
    elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
        set(GLEW_LIBRARIES "libGLEW.dylib")
    endif()

endif()

## CXX Flags print out:
message(STATUS "USED CXX Flags: ${CMAKE_CXX_FLAGS}")

message(STATUS "Possible CXX_FLAGS for platform: ")
message("       CMAKE_CXX_FLAGS_DEBUG is ${CMAKE_CXX_FLAGS_DEBUG}")
message("       CMAKE_CXX_FLAGS_RELEASE is ${CMAKE_CXX_FLAGS_RELEASE}")
message("       CMAKE_CXX_FLAGS_RELWITHDEBINFO is ${CMAKE_CXX_FLAGS_RELWITHDEBINFO}")
message("       CMAKE_CXX_FLAGS_MINSIZEREL is ${CMAKE_CXX_FLAGS_MINSIZEREL}")

## Setting SGE directory
set (SGE_DIR "SimpleGameEngine")

## Setting Game directory
set (Game_DIR "ZombieGame")

## Add include paths
include_directories(${SGE_DIR})

include_directories(${SGE_DIR}/Action_lib/Action)
include_directories(${SGE_DIR}/Action_lib/Action/Actions)

include_directories(${SGE_DIR}/IO_lib/InputManager)
include_directories(${SGE_DIR}/IO_lib/IOManager)
include_directories(${SGE_DIR}/IO_lib/KeyboardState)
include_directories(${SGE_DIR}/IO_lib/Mouse)
include_directories(${SGE_DIR}/IO_lib/Key)

include_directories(${SGE_DIR}/Level_lib/Level)
include_directories(${SGE_DIR}/Level_lib/LevelParser)

include_directories(${SGE_DIR}/Logic_lib/Logic)
include_directories(${SGE_DIR}/Logic_lib/Logic/Logics/Camera)
include_directories(${SGE_DIR}/Logic_lib/Logic/Logics/Colliders)
include_directories(${SGE_DIR}/Logic_lib/Logic/Logics/Movers)

include_directories(${SGE_DIR}/Object_lib/Camera2d)
include_directories(${SGE_DIR}/Object_lib/Object)
include_directories(${SGE_DIR}/Object_lib/Object/BackgroundElement)
include_directories(${SGE_DIR}/Object_lib/Object/Interface)
include_directories(${SGE_DIR}/Object_lib/Object/Reactive)
include_directories(${SGE_DIR}/Object_lib/Object/Shape)

include_directories(${SGE_DIR}/Game_lib/Director)
include_directories(${SGE_DIR}/Game_lib/Game)
include_directories(${SGE_DIR}/Game_lib/InputHandler)
include_directories(${SGE_DIR}/Game_lib/ActionHandler)

include_directories(${SGE_DIR}/Renderer_lib/Renderer)
include_directories(${SGE_DIR}/Renderer_lib/CameraHandler)
include_directories(${SGE_DIR}/Renderer_lib/ResourceManager)
include_directories(${SGE_DIR}/Renderer_lib/Shaders)
include_directories(${SGE_DIR}/Renderer_lib/Sprite)
include_directories(${SGE_DIR}/Renderer_lib/SpriteBatch)
include_directories(${SGE_DIR}/Renderer_lib/TextureCache)
include_directories(${SGE_DIR}/Renderer_lib/TextureLoader)
include_directories(${SGE_DIR}/Renderer_lib/WindowManager)

include_directories(${SGE_DIR}/Scene_lib/Scene)

include_directories(${SGE_DIR}/ThirdParty_Librarys/PicoPNG) 
include_directories(${SGE_DIR}/ThirdParty_Librarys/Box2D) 

include_directories(${SGE_DIR}/Utils_lib/Timing)
include_directories(${SGE_DIR}/Utils_lib/Utils)
include_directories(${SGE_DIR}/Utils_lib/Logger)

## Add subdirectories:

## SGE lib:
add_subdirectory(${SGE_DIR})

## ZombieGame:
add_subdirectory(${Game_DIR})

if(WIN32)
	file(GLOB CONAN_DLLS "dlls/*.dll")
	file(COPY ${CONAN_DLLS} DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/bin")
	file(GLOB CONAN_PDBS "dlls/*.pdb")
	file(COPY ${CONAN_PDBS} DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/bin")
endif()

## More info:
message(STATUS "CMAKE_MODULE_LINKER_FLAGS: ${CMAKE_MODULE_LINKER_FLAGS}")
message(STATUS "CMAKE_SHARED_LINKER_FLAGS: ${CMAKE_SHARED_LINKER_FLAGS}")
message(STATUS "CMAKE_INCLUDE_PATH: ${CMAKE_INCLUDE_PATH}")
message(STATUS "CMAKE_LIBRARY_PATH: ${CMAKE_LIBRARY_PATH}")