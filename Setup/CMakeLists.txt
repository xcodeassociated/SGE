cmake_minimum_required(VERSION 3.5)
project(SGE-ZombieGame-setup)

set(INSTALL_DEPENDENCIES_DIR "${CMAKE_SOURCE_DIR}/build" CACHE STRING "" FORCE)

option(PROCESSOR_COUNT "Set processor count, default 4" "4")

set(PROCESSOR_COUNT 4) ## temp

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
include(ExternalSDL2.cmake)
include(ExternalGLM.cmake)
include(ExternalGLEW.cmake)


add_custom_command(TARGET BOOST_EXTERNAL
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/build/boost/lib/*.dylib ${CMAKE_CURRENT_SOURCE_DIR}/build/bin)

set_target_properties(BOOST_EXTERNAL PROPERTIES
        BUILD_WITH_INSTALL_RPATH TRUE
        INSTALL_RPATH_USE_LINK_PATH TRUE)

add_custom_command(TARGET GLEW_EXTERNAL
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/build/glew/lib/*.dylib ${CMAKE_CURRENT_SOURCE_DIR}/build/bin)

add_custom_command(TARGET SDL2_EXTERNAL
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/build/sdl/lib/*.dylib ${CMAKE_CURRENT_SOURCE_DIR}/build/bin)



add_custom_command(TARGET BOOST_EXTERNAL
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/build/boost/lib/*.a ${CMAKE_CURRENT_SOURCE_DIR}/build/bin)

set_target_properties(BOOST_EXTERNAL PROPERTIES
        BUILD_WITH_INSTALL_RPATH TRUE
        INSTALL_RPATH_USE_LINK_PATH TRUE)

add_custom_command(TARGET GLEW_EXTERNAL
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/build/glew/lib/*.a ${CMAKE_CURRENT_SOURCE_DIR}/build/bin)

add_custom_command(TARGET SDL2_EXTERNAL
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/build/sdl/lib/*.a ${CMAKE_CURRENT_SOURCE_DIR}/build/bin)
