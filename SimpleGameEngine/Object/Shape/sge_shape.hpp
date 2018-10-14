#ifndef SGE_SHAPE_HPP
#define SGE_SHAPE_HPP

#include "sge_shape_type.hpp"

namespace SGE
{
	/**
	 * \brief 
	 */
	class Shape
	{
	private:
		/**
		 * \brief 
		 */
		ShapeType type = ShapeType::None;
		/**
		 * \brief 
		 */
		bool disposable = true;

	protected:
		/**
		 * \brief 
		 */
		Shape() = default;
		/**
		 * \brief 
		 */
		Shape(const Shape&) = default;
		/**
		 * \brief 
		 * \param type 
		 */
		Shape(ShapeType type);
		/**
		 * \brief 
		 * \param type 
		 * \param disposable 
		 */
		Shape(ShapeType type, bool disposable);

		// Shape can be abstract, to prevent creation of shape objects. 
	public:
		/**
		 * \brief 
		 */
		virtual ~Shape();

		//Should not be overidden
		/**
		 * \brief 
		 * \return 
		 */
		ShapeType getType() const;


		virtual float getWidth() const = 0;
		virtual float getHeight() const = 0;

		//Checks if object shape is disposable
		/**
		 * \brief 
		 * \return 
		 */
		bool isDisposable();
	};

}

#endif // !SGE_SHAPE_HPP
