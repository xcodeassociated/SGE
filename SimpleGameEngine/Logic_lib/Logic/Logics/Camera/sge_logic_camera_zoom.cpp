#include "sge_logic_camera_zoom.hpp"
#include <sge_keyboard_state.hpp>
#include <sge_camera2d.hpp>
#include "sge_object_bind.hpp"

SGE::Logics::CameraZoom::CameraZoom(const float speed, const float min, const float max, const SGE::Key in, const SGE::Key out): Logic(LogicPriority::Highest), speed(speed), minZoom(min), maxZoom(max), zoomIn(in), zoomOut(out)
{
}

void SGE::Logics::CameraZoom::performLogic(const ObjectBind& camObj)
{
	auto cam = reinterpret_cast<Camera2d*>(camObj[0]);
	auto scale = cam->getScale();

	if (isPressed(this->zoomIn)) scale += this->speed;
	if (this->minZoom < scale) scale = this->minZoom;
	if (isPressed(this->zoomOut)) scale -= this->speed;
	if (this->maxZoom > scale) scale = this->maxZoom;

	cam->setScale(scale);
}
