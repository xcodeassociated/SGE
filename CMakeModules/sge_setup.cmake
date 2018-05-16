set(INSTALL_RPATH_USE_LINK_PATH TRUE)

set(BOOST_ROOT "${SETUP_BUILD_DIR}/boost")

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