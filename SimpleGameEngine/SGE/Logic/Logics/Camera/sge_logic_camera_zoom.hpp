#ifndef sge_logic_camera_zoom_h
#define sge_logic_camera_zoom_h

#include "../../sge_logic.hpp"

namespace SGE
{
	namespace Logics
	{
		class CameraZoom : public Logic
		{
			float speed, maxZoom, minZoom;
			const Key zoomIn, zoomOut;
		public:
			CameraZoom(const float speed, const float min, const float max, const SGE::Key in, const SGE::Key out)
				:Logic(LogicPriority::Highest), speed(speed), minZoom(min), maxZoom(max), zoomIn(in), zoomOut(out) {}
			~CameraZoom() = default;

			void performLogic(SGE::Object::ID camObj) override
			{
				auto cam = reinterpret_cast<Camera2d*>(camObj.getObject());
				auto scale = cam->getScale();
				//std::cout << scale << ' ';
				if (isPressed(this->zoomIn)) scale += this->speed;
				if (this->minZoom < scale) scale = this->minZoom;
				if (isPressed(this->zoomOut)) scale -= this->speed;
				if (this->maxZoom > scale) scale = this->maxZoom;
				cam->setScale(scale);
				//std::cout << scale << std::endl;
			}
		};
	}
}

#endif // !sge_logic_camera_zoom_h
