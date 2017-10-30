#ifndef SGE_SHAPE_HPP
#define SGE_SHAPE_HPP

#include "sge_shape_type.hpp"

namespace SGE
{
	class Shape
	{
	private:
		ShapeType type = ShapeType::None;
		bool disposable = true;

	protected:
		Shape() = default;
		Shape(const Shape&) = default;
		Shape(ShapeType type);
		Shape(ShapeType type, bool disposable);

		// Shape can be abstract, to prevent creation of shape objects. 
	public:
		virtual ~Shape();

		//Should not be overidden
		ShapeType getType() const;

		//Checks if object shape is disposable
		bool isDisposable();
	};

}

#endif // !SGE_SHAPE_HPP
