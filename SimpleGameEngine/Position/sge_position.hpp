#ifndef sge_position_h
#define sge_position_h

#include <glm/glm.hpp>

namespace SGE
{
    struct Position
    {
        float x = 0;
        float y = 0;

        Position(float _x, float _y) : x(_x), y(_y) {};
        Position() = default;

		void setX(const float x)
		{
			this->x = x;
		}

		void setY(const float y)
		{
			this->y = y;
		}

		float getX() const
		{
			return this->x;
		}

		float getY() const
		{
			return this->y;
		}

		glm::vec2 getPosition() const
		{
			return {this->x, this->y};
		}
    };
}
#endif
