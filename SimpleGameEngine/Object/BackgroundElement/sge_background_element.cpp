#include "sge_background_element.hpp"

SGE::BackgroundElement::BackgroundElement(float x, float y, std::string path): Object(x, y, true, SGE::Shape::BaseTile()), path(path)
{}

const std::string& SGE::BackgroundElement::getPath() const
{
	return this->path;
}
