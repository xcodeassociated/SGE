set(SpriteSOURCES
        sge_sprite.hpp
        sge_sprite.cpp)

add_library(Sprite
        ${SpriteSOURCES})

target_link_libraries(Sprite Shape)

install(TARGETS Sprite DESTINATION "${CMAKE_INSTALL_PREFIX}/lib")