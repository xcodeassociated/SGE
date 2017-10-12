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

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

## Flag for exporting symbols -- needed to combine shared libs for SGE
set(CMAKE_SHARED_LINKER_FLAGS "-Wl,--export-all-symbols")

if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    message(STATUS "Linux")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fext-numeric-literals")
endif()

## FINDING MODULES
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake_modules")

## Boost:
find_package(Boost COMPONENTS program_options system filesystem REQUIRED)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})

    message(STATUS "Boost Found!")
    message(STATUS "Boost version: ${Boost_VERSION}")
    message(STATUS "Boost include: ${Boost_INCLUDE_DIRS}")
    message(STATUS "Boost libs: ${Boost_LIBRARY_DIRS}")
endif()

## SDL:
find_package(SDL2 REQUIRED)
#find_package(SDL2_image REQUIRED)
#find_package(SDL2_ttf REQUIRED)
include_directories(${SDL2_INCLUDE_DIR}) #${SDL2_IMAGE_INCLUDE_DIR} ${SDL2_TTF_INCLUDE_DIR})

if (NOT SDL2_FOUND)
	message(Error "SDL2 not found")
endif()
#if (NOT SDL2_IMAGE_FOUND)
#	message(Error "SDL2 IMAGE not found")
#endif()
#if (NOT SDL2_TTF_FOUND)
#	message(Error "SDL2 TTF not found")
#endif()

## GLM:
find_package(GLM REQUIRED)
include_directories(${GLM_INCLUDE_DIRS})
link_directories(${GLM_LIBRARY_DIRS})
add_definitions(${GLM_DEFINITIONS})

if(NOT GLM_FOUND)
        message(Error "GLM not found")
endif()

## OpenGL: -- TODO: check if needed
find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})

if(NOT OpenGL_FOUND)
        message(Error "OpenGL not found")
endif()

## Setting SGE directory
set (SGE_DIR "SimpleGameEngine")

## Setting Game directory
set (Game_DIR "ZombieGame")

## Add include paths
include_directories(${SGE_DIR}) ##TODO: this includes SGE.hpp -- REFACTOR needed!

include_directories(${SGE_DIR}/Action_lib/Action)
include_directories(${SGE_DIR}/Action_lib/Action/Actions)
include_directories(${SGE_DIR}/Action_lib/Action/ActionHandler)

include_directories(${SGE_DIR}/include) ## TODO: this file has to removed -- REFACTOR needed!

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

