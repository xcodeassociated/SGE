#ifndef SGE_SHAPE_HPP
#define SGE_SHAPE_HPP

#include "sge_shape_type.hpp"

namespace SGE
{
	class Shape
	{
		ShapeType type = ShapeType::None;

		bool disposable = true;

	protected:

		Shape() = default;

		Shape(const Shape&) = default;

		Shape(ShapeType type);

		Shape(ShapeType type, bool disposable);

	public:
		virtual ~Shape();

		ShapeType getType() const;

		bool isDisposable();
	};

}

#endif // !SGE_SHAPE_HPP
