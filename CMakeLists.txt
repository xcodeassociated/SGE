cmake_minimum_required(VERSION 3.5)

## Project name 
project(SGE-ZombieGame)

## include conan cmake file
include(${CMAKE_CURRENT_SOURCE_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

## include custom cmake modules
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

message(STATUS "Source DIR: ${CMAKE_CURRENT_SOURCE_DIR}")
message (STATUS "Build DIR: ${CMAKE_CURRENT_BINARY_DIR}")

set(CMAKE_VERBOSE_MAKEFILE on)

set(CMAKE_CXX_STANDARD 14)

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

elseif(WIN32)
    message(STATUS "WIN32")
    ## Force exports without adding macros in sources.
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS 1)
    ## TODO: WIN32 compiler flags here!!!
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W1")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Za")
    ## Adds export libraries directory
    link_directories("${CMAKE_CURRENT_BINARY_DIR}/lib")

endif()

## FINDING MODULES
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMakeModules")

## Boost:
find_package(Boost COMPONENTS program_options system REQUIRED) #TODO: filesystem <-- missing in conan boost (mac)
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

## Setting SGE directory
set (SGE_DIR "SimpleGameEngine")

## Setting Game directory
set (Game_DIR "ZombieGame")

## Add include paths
include_directories(${SGE_DIR}) ##TODO: this includes SGE.hpp -- REFACTOR needed!

include_directories(${SGE_DIR}/Action_lib/Action)
include_directories(${SGE_DIR}/Action_lib/Action/Actions)
include_directories(${SGE_DIR}/Action_lib/ActionHandler)

include_directories(${SGE_DIR}/IO_lib/InputManager)
include_directories(${SGE_DIR}/IO_lib/IOManager)
include_directories(${SGE_DIR}/IO_lib/KeyBoardState)
include_directories(${SGE_DIR}/IO_lib/Mouse)

include_directories(${SGE_DIR}/Level_lib/Level)
include_directories(${SGE_DIR}/Level_lib/LevelParser)

include_directories(${SGE_DIR}/Logic_lib/Logic)
include_directories(${SGE_DIR}/Logic_lib/Logics/Camera)
include_directories(${SGE_DIR}/Logic_lib/Logics/Colliders)
include_directories(${SGE_DIR}/Logic_lib/Logics/Movers)

include_directories(${SGE_DIR}/Object_lib/Camera2d)
include_directories(${SGE_DIR}/Object_lib/ID)
include_directories(${SGE_DIR}/Object_lib/Object)
include_directories(${SGE_DIR}/Object_lib/Object/BackgroundElement)
include_directories(${SGE_DIR}/Object_lib/Object/Interface)
include_directories(${SGE_DIR}/Object_lib/Object/Reactive)
include_directories(${SGE_DIR}/Object_lib/Object/Shape)

include_directories(${SGE_DIR}/ObjectManager_lib/ObjectManager)
include_directories(${SGE_DIR}/ObjectManager_lib/Relay)

include_directories(${SGE_DIR}/Renderer_lib/ResourceManager)
include_directories(${SGE_DIR}/Renderer_lib/Shaders)
include_directories(${SGE_DIR}/Renderer_lib/Sprite)
include_directories(${SGE_DIR}/Renderer_lib/SpriteBatch)
include_directories(${SGE_DIR}/Renderer_lib/TextureCache)
include_directories(${SGE_DIR}/Renderer_lib/TextureLoader)

include_directories(${SGE_DIR}/Scene_lib/Director)
include_directories(${SGE_DIR}/Scene_lib/Scene)


include_directories(${SGE_DIR}/ThirdParty_Librarys/PicoPNG) 
include_directories(${SGE_DIR}/Utils_lib/Timing)
include_directories(${SGE_DIR}/Utils_lib/Utils)

## Add subdirectories:

## SGE lib:
add_subdirectory(${SGE_DIR})

## ZombieGame:
add_subdirectory(${Game_DIR})

