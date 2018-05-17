#include "sge_level.hpp"

SGE::Level::Level(size_t x, size_t y): height(y), width(x)
{
}

const size_t& SGE::Level::getHeight() const
{
	return this->height;
}

const size_t& SGE::Level::getWidth() const
{
	return this->width;
}

std::vector<SGE::BackgroundElement>& SGE::Level::getBackground()
{
	return this->background;
}

std::vector<SGE::WorldElement>& SGE::Level::getWorld()
{
	return this->world;
}

void SGE::Level::clear()
{
	this->background.clear();
	this->world.clear();
}
