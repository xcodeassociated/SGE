#ifndef sge_logic_move_h
#define sge_logic_move_h

#include "../../sge_logic.hpp"
#include "../../../IO/Key/sge_key.hpp"

namespace SGE
{
	namespace Logics
	{
		/**
		 * \brief 
		 */
		class SimpleMove : public Logic
		{
			/**
			 * \brief 
			 */
			float speed = 0;
			/**
			 * \brief 
			 */
			const Key up;
			/**
			 * \brief 
			 */
			const Key down;
			/**
			 * \brief 
			 */
			const Key left;
			/**
			 * \brief 
			 */
			const Key right;

			Object* object = nullptr;

		public:
			/**
			 * \brief 
			 * \param speed 
			 * \param up 
			 * \param down 
			 * \param left 
			 * \param right 
			 */
			SimpleMove(Object* object, const float speed, const SGE::Key up, const SGE::Key down, const SGE::Key left, const SGE::Key right);
			/**
			 * \brief 
			 */
			~SimpleMove() = default;

			/**
			 * \brief 
			 * \param obj 
			 */
			void performLogic() override;
		};
	}
}

#endif //!sge_logic_move_h
