#ifndef SGE_LEVEL_HPP
#define SGE_LEVEL_HPP

#include "../BackgroundElement/sge_background_element.hpp"

namespace SGE
{
	class Level
	{
	private:
		size_t height = 0;
		size_t width = 0;
		std::vector<BackgroundElement> background;
	public:
		Level() = default;
		Level(size_t x, size_t y) : height(y),width(x){}
		Level(Level&&) = default;
		Level& operator=(Level&&) = default;

		const size_t& getHeight()
		{
			return this->height;
		}

		const size_t& getWidth()
		{
			return this->width;
		}

		std::vector<BackgroundElement>& getBackground()
		{
			return this->background;
		}
	};
}

#endif // !SGE_LEVEL_HPP
