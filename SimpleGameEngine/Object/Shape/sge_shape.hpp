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
		float width = 0.f;
		float height = 0.f;
		float radius = 0.f;
		bool disposable = false;

	protected:
		constexpr Shape() = default;
		constexpr Shape(ShapeType type, float width, float height, float radius, bool disposable)
			:type(type), width(width), height(height), radius(radius), disposable(disposable) {}
	public:
		~Shape() = default;
		constexpr Shape(const Shape&) = default;
		static Shape* BaseTile()
		{
			static Shape baseTile(ShapeType::Rectangle, 1.f, 1.f, sqrt(2.f), false);
			return &baseTile;
		}

		static Shape* Shapeless()
		{
			static Shape shapeless;
			return &shapeless;
		}

		static Shape* Circle(float radius, bool disposable = false)
		{
			return new Shape(ShapeType::Circle, radius*2.f, radius*2.f, radius, disposable);
		}

		static Shape* Rectangle(float width, float height, bool disposable = false)
		{
			return new Shape(ShapeType::Rectangle, width, height, 0.5f*sqrt(width*width+height*height), disposable);
		}
		/**
		 * \brief 
		 * \return 
		 */
		constexpr ShapeType getType() const
		{
			return this->type;
		}
		constexpr float getWidth() const
		{
			return this->width;
		}
		constexpr float getHeight() const
		{
			return this->height;
		}
		constexpr float getRadius() const
		{
			return this->radius;
		}

		constexpr float getWidthGLM() const
		{
			return this->width * 64.f;
		}
		constexpr float getHeightGLM() const
		{
			return this->height * 64.f;
		}
		constexpr float getRadiusGLM() const
		{
			return this->radius * 64.f;
		}

		/**
		 * \brief Checks if object shape is disposable
		 * \return 
		 */
		constexpr bool isDisposable() const
		{
			return this->disposable;
		}
	};
}

#endif // !SGE_SHAPE_HPP
