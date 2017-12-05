#include "sge_utils.hpp"

#include <SDL2/SDL.h>

#include "sge_macro.hpp"

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
	_screenCoords.y = SCREEN_HEIGHT - _screenCoords.y;
    _screenCoords -= glm::vec2(SCREEN_WIDTH * 0.5, SCREEN_HEIGHT * 0.5);
	_screenCoords /= scale;
	_screenCoords += coords;

	return _screenCoords;
}
