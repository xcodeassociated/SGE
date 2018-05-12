cmake_minimum_required(VERSION 3.5)
project(SGE-ZombieGame)
  
## Package Manager option handling section
option(PACKAGE_MANAGER "Default project package manager default: NONE" NONE)

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

set(SGE_DIR "SimpleGameEngine")
set(Game_DIR "ZombieGame")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/$<CONFIG>")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/$<CONFIG>")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH ON)

message(STATUS "BUILD_SHARED_LIBS: ${BUILD_SHARED_LIBS}")
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
message(STATUS "INSTALL_DEPENDENCIES_DIR: ${INSTALL_DEPENDENCIES_DIR}")
message(STATUS "Package Manager: ${PKG}")

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

        set(CMAKE_MACOSX_RPATH ON)
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

	## GLEW: 
	find_package(GLEW REQUIRED)
	if (NOT GLEW_FOUND)
		message(Error "GLEW not found")
	endif()

	## GLM:
	find_package(GLM)
	if (NOT GLM_INCLUDE_DIRS)
		message(WARNING "GLM not found! GLM includes may not be found")
	else()
		include_directories(${GLM_INCLUDE_DIRS})
	endif()

elseif(PKG STREQUAL "LOCAL")
	message(STATUS "Using PACKAGE_MANAGER: LOCAL")
    message(STATUS "SETUP_BUILD_DIR: ${SETUP_BUILD_DIR}")

    set(INSTALL_RPATH_USE_LINK_PATH TRUE)

    set(BOOST_ROOT "${CMAKE_SOURCE_DIR}/${SETUP_BUILD_DIR}/boost")
	set(BOOST_LIBRARYDIR "${BOOST_ROOT}/lib")
	set(BOOST_INCLUDEDIR "${BOOOT_ROOT}/include/boost-1_65_1")
	
	if (WIN32 AND NOT Boost_COMPILER)
		message(WARNING "On windows, please pass `Boost_COMPILER` (e.g. -DBoost_COMPILER=-vc1413 -- for VS2017)")
    endif()

	set(Boost_USE_MULTITHREADED ON)
	set(Boost_USE_STATIC_LIBS ON)

	set(BOOST_DEBUG ON)

	## GLM:
	set(GLM_ROOT "${SETUP_BUILD_DIR}/glm")
	set(GLM_INCLUDE_DIRS "${SETUP_BUILD_DIR}/glm")
	include_directories(${GLM_INCLUDE_DIRS})

	## GLEW:
    if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
		## so far glew from setup project works only on macOS
        set(GLEW_ROOT "${SETUP_BUILD_DIR}/glew")
        set(GLEW_INCLUDE_DIR "${SETUP_BUILD_DIR}/glew/include")
        set(GLEW_LIBRARY_DIR "${SETUP_BUILD_DIR}/glew/lib")
        set(GLEW_LIBRARIES "libGLEW.a")
    else()
        find_package(GLEW)
        if (NOT GLEW_FOUND)
            message(WARNING "GLEW not found! The linking may not succeed.")
        endif()
    endif()

    include_directories(${GLEW_INCLUDE_DIR})
    link_directories(${GLEW_LIBRARY_DIR})

else()
	message(STATUS "Using PACKAGE_MANAGER: NONE")
	message(STATUS "No ROOT for libs will be set up")
	message(STATUS "CMAKE_TOOLCHAIN_FILE: ${CMAKE_TOOLCHAIN_FILE}")

	## GLEW:
	find_package(GLEW REQUIRED)
	if (NOT GLEW_FOUND)
		message(Error "GLEW not found")
	endif()

	## GLM:
	find_package(GLM)
	if (NOT GLM_INCLUDE_DIRS)
		message(WARNING "GLM not found! GLM includes may not be found")
	else()
		include_directories(${GLM_INCLUDE_DIRS})
	endif()

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

## Debug info:
message(STATUS "GLM_ROOT: ${GLM_ROOT}")
message(STATUS "	GLM_INCLUDE_DIRS: ${GLM_INCLUDE_DIRS}")

message(STATUS "BOOST_ROOT: ${BOOST_ROOT}")
message(STATUS "    Boost_FOUND: ${Boost_FOUND}")
message(STATUS "    Boost_VERSION: ${Boost_VERSION}")
message(STATUS "    Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
message(STATUS "    Boost_LIBRARIES: ${Boost_LIBRARIES}")
message(STATUS "    Boost_LIBRARY_DIRS: ${Boost_LIBRARY_DIRS}")

message(STATUS "SDL2_ROOT: ${SDL2_DIR}")
message(STATUS "	SDL2_INCLUDE_DIR: ${SDL2_INCLUDE_DIR}")
message(STATUS "	SDL2_DEFINITIONS: ${SDL2_DEFINITIONS}")
message(STATUS "	SDL2_LIBRARIES: ${SDL2_LIBRARIES}")

message(STATUS "GLEW_ROOT: ${GLEW_ROOT}")
message(STATUS "	GLEW_INCLUDE_DIRS: ${GLEW_INCLUDE_DIRS}")
message(STATUS "	GLEW_LIBRARY_DIRS: ${GLEW_LIBRARY_DIRS}")
message(STATUS "	GLEW_DEFINITIONS: ${GLEW_DEFINITIONS}")
message(STATUS "    GLEW_LIBRARIES: ${GLEW_LIBRARIES}")

message(STATUS "OpenGL: ")
message(STATUS "	OpenGL_INCLUDE_DIRS: ${OpenGL_INCLUDE_DIRS}")
message(STATUS "	OpenGL_LIBRARY_DIRS: ${OpenGL_LIBRARY_DIRS}")
message(STATUS "	OpenGL_DEFINITIONS: ${OpenGL_DEFINITIONS}")

## CXX Flags print out:
message(STATUS "USED CXX Flags: ${CMAKE_CXX_FLAGS}")

message(STATUS "Possible CXX_FLAGS for platform: ")
message("       CMAKE_CXX_FLAGS_DEBUG is ${CMAKE_CXX_FLAGS_DEBUG}")
message("       CMAKE_CXX_FLAGS_RELEASE is ${CMAKE_CXX_FLAGS_RELEASE}")
message("       CMAKE_CXX_FLAGS_RELWITHDEBINFO is ${CMAKE_CXX_FLAGS_RELWITHDEBINFO}")
message("       CMAKE_CXX_FLAGS_MINSIZEREL is ${CMAKE_CXX_FLAGS_MINSIZEREL}")

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

include_directories(${SGE_DIR}/Logic_lib)
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

include_directories(${SGE_DIR}/Utils_lib)
include_directories(${SGE_DIR}/Utils_lib/Timing)
include_directories(${SGE_DIR}/Utils_lib/Utils)
include_directories(${SGE_DIR}/Utils_lib/Logger)

add_subdirectory(${SGE_DIR})
add_subdirectory(${Game_DIR})

message(STATUS "CMAKE_MODULE_LINKER_FLAGS: ${CMAKE_MODULE_LINKER_FLAGS}")
message(STATUS "CMAKE_SHARED_LINKER_FLAGS: ${CMAKE_SHARED_LINKER_FLAGS}")
message(STATUS "CMAKE_INCLUDE_PATH: ${CMAKE_INCLUDE_PATH}")
message(STATUS "CMAKE_LIBRARY_PATH: ${CMAKE_LIBRARY_PATH}")