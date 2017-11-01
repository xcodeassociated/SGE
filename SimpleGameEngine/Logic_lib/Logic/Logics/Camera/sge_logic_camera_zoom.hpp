#ifndef sge_logic_camera_zoom_h
#define sge_logic_camera_zoom_h

#include "sge_logic.hpp"
#include "sge_action_handler.hpp"
#include "sge_key.hpp"

namespace SGE
{
	namespace Logics
	{
		/**
		 * \brief 
		 */
		class CameraZoom : public Logic
		{
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
			CameraZoom(const float speed, const float min, const float max, const SGE::Key in, const SGE::Key out);
			/**
			 * \brief 
			 */
			~CameraZoom() = default;

			/**
			 * \brief 
			 * \param camObj 
			 */
			void performLogic(const ObjectBind& camObj) override;
		};
	}
}

#endif // !sge_logic_camera_zoom_h
