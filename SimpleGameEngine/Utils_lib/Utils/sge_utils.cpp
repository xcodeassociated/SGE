#include "sge_utils.hpp"

#include <SDL2/SDL.h>

#define SCREEN_HEIGHT 1024
#define SCREEN_WIDTH 768

const std::string& SGE::getPath()
{
	static std::string base_path = []()-> std::string
	{
		char* path = SDL_GetBasePath();
		std::string ret;
		if (path)
		{
			ret = std::string(path);
			SDL_free(path);
		}
		else
		{
			ret = std::string("./");
		}
		return ret;
	}();
	return base_path;
}

glm::vec2 SGE::screenToWorld(glm::vec2 _screenCoords, glm::vec2 coords, double scale)
{
	//invert y axis
	_screenCoords.y = SCREEN_HEIGHT - _screenCoords.y;

	//0 is center & scaling & set position
	_screenCoords -= glm::vec2(SCREEN_WIDTH * 0.5, SCREEN_HEIGHT * 0.5);
	_screenCoords /= scale;
	_screenCoords.x += coords.x;
	_screenCoords.y += coords.y;

	return _screenCoords;
}
