set(Camera2dSOURCES
        sge_camera2d.hpp
        sge_camera2d.cpp)

add_library(Camera2d ${Camera2dSOURCES})

target_link_libraries(Camera2d Utils)

install(TARGETS Camera2d DESTINATION "${CMAKE_INSTALL_PREFIX}/lib")