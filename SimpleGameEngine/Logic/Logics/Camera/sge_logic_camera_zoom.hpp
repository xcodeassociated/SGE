#ifndef sge_logic_camera_zoom_h
#define sge_logic_camera_zoom_h

#include "../../sge_logic.hpp"
#include "../../../IO/Key/sge_key.hpp"

namespace SGE
{
	class Camera2d;

	namespace Logics
	{
		/**
		 * \brief 
		 */
		class CameraZoom : public Logic
		{
			Camera2d* cameraObject = nullptr;

			/**
			 * \brief 
			 */
			float speed;
			/**
			 * \brief 
			 */
			float maxZoom;
			/**
			 * \brief 
			 */
			float minZoom;
			/**
			 * \brief 
			 */
			const Key zoomIn;
			/**
			 * \brief 
			 */
			const Key zoomOut;

		public:
			/**
			 * \brief 
			 * \param speed 
			 * \param min 
			 * \param max 
			 * \param in 
			 * \param out 
			 */
			CameraZoom(Camera2d* camera, const float speed, const float min, const float max, const SGE::Key in, const SGE::Key out);
			/**
			 * \brief 
			 */
			~CameraZoom() = default;

			/**
			 * \brief 
			 * \param camObj 
			 */
			void performLogic() override;
		};
	}
}

#endif // !sge_logic_camera_zoom_h
