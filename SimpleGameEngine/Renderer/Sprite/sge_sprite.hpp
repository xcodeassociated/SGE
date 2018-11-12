#pragma once

#ifndef sprite_h
#define sprite_h
#include <vec2.hpp>

namespace SGE
{
	/**
     * \brief 
     */
    struct Sprite
	{
		Sprite(const glm::vec2 position, const glm::vec2 scale, const float rotation, const float layer)
			: position(position), scale(scale), rotation(rotation), layer(layer) {};
		Sprite() = default;
		~Sprite() = default;

	    glm::vec2 position = {0.f,0.f};
		glm::vec2 scale = {0.f,0.f};
		float rotation = 0.f;
		float layer = 0.f;
    };
}

#endif /* sprite_h */
