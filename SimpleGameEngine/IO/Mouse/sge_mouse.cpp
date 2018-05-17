#include "sge_mouse.hpp"

SGE::MouseObject::MouseObject() noexcept: mouseCoords(0.0f, 0.0f)
{
}

void SGE::MouseObject::setMouseCoords(glm::vec2 coords) noexcept
{
	this->mouseCoords = coords;
}

glm::vec2 SGE::MouseObject::getMouseCoords() const noexcept
{
	return this->mouseCoords;
}
