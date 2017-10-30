#include "sge_background_element.hpp"
#include "sge_shape_rectangle.hpp"

SGE::BackgroundElement::BackgroundElement(float x, float y, std::string path): Object(x, y, true, getBaseTileShape()), path(path)
{
}

const std::string& SGE::BackgroundElement::getPath() const
{
	return this->path;
}
