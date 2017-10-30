#ifndef sge_logic_camera_zoom_h
#define sge_logic_camera_zoom_h

#include "sge_logic.hpp"
#include "sge_action_handler.hpp"
#include "sge_key.hpp"

namespace SGE
{
	namespace Logics
	{
		class CameraZoom : public Logic
		{
			float speed, maxZoom, minZoom;
			const Key zoomIn, zoomOut;
		public:
			CameraZoom(const float speed, const float min, const float max, const SGE::Key in, const SGE::Key out);
			~CameraZoom() = default;

			void performLogic(const ObjectBind& camObj) override;
		};
	}
}

#endif // !sge_logic_camera_zoom_h
