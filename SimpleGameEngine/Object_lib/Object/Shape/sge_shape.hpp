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

	Shape* getShapeless();

	class Shapeless : public Shape
	{
		Shapeless();

	public:
		//Single Flyweight for no shape objects?
		friend Shape* getShapeless();
	};

	class Circle : public Shape
	{
	private:
		float radius = 0.f;

	public:
		Circle();
		Circle(const Circle&) = default;
		explicit Circle(float radius);
		Circle(float radius, bool disposable);

		float getRadius() const;

		void setRadius(float radius);
	};

	class Rectangle : public Shape
	{
	private:
		float width = 0.f;
		float height = 0.f;

	public:
		Rectangle();
		Rectangle(const Rectangle&) = default;
		explicit Rectangle(float width, float height);
		Rectangle(float width, float height, bool disposable);

		float getWidth() const;

		void setWidth(const float width);

		float getHeight() const;

		void setHeight(const float height);
	};
	
	Rectangle* getBaseTileShape();
}

#endif // !SGE_SHAPE_HPP
