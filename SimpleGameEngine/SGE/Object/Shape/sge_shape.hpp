#ifndef SGE_SHAPE_HPP
#define SGE_SHAPE_HPP

namespace SGE
{
	enum class ShapeType : char
	{
		Circle,
		Rectangle,
		None
	};

	class Shape
	{
	private:
		ShapeType type = ShapeType::None;
		bool disposable = true;

	protected:
		Shape() = default;
		Shape(const Shape&) = default;
		Shape(ShapeType type) :type(type) {}
		Shape(ShapeType type, bool disposable) : type(type), disposable(disposable){}
		
		// Shape can be abstract, to prevent creation of shape objects. 
	public:
		virtual ~Shape() {}

		//Should not be overidden
		ShapeType getType() const
		{
			return this->type;
		}

		//Checks if object shape is disposable
		bool isDisposable()
		{
			return this->disposable;
		}
	};

	Shape* getShapeless();

	class Shapeless : public Shape
	{
		Shapeless() : Shape(ShapeType::None,false)
		{}
		
	public:
		//Single Flyweight for no shape objects?
		friend Shape* getShapeless()
		{
			static Shapeless s;
			return &s;
		}
	};

	class Circle : public Shape
	{
	private:
		float radius = 0.f;

	public:
		Circle(): Shape(ShapeType::Circle){}
		Circle(const Circle&) = default;
		explicit Circle(float radius): Shape(ShapeType::Circle), radius(radius){}
		Circle(float radius, bool disposable): Shape(ShapeType::Circle, disposable), radius(radius) {}

		float getRadius() const
		{
			return this->radius;
		}

		void setRadius(float radius)
		{
			this->radius = radius;
		}
	};

	class Rectangle : public Shape
	{
	private:
		float width = 0.f;
		float height = 0.f;

	public:
		Rectangle() : Shape(ShapeType::Rectangle) {}
		Rectangle(const Rectangle&) = default;
		explicit Rectangle(float width, float height) : Shape(ShapeType::Rectangle), width(width), height(height) {}
		Rectangle(float width, float height, bool disposable) : Shape(ShapeType::Rectangle, disposable), width(width), height(height) {}

		float getWidth() const
		{
			return width;
		}

		void setWidth(const float width)
		{
			this->width = width;
		}

		float getHeight() const
		{
			return height;
		}

		void setHeight(const float height)
		{
			this->height = height;
		}
	};

	Shape* getBaseTileShape()
	{
		static Rectangle tile(64, 64, 0);
		return &tile;
	}
}

#endif // !SGE_SHAPE_HPP
