#ifndef sge_object_h
#define sge_object_h

#include "../Shape/sge_shape.hpp"
#include "../Shape/sge_shapeless.hpp"
#include "Texture/sge_texture.hpp"

#include <glm/vec2.hpp>
#include <GL/glew.h>
#include <string>

namespace SGE
{   
	class Sprite
	{   
	protected:
		float X = 0.f;
		float Y = 0.f;

		bool drawable = false;
		bool visible = false;
	
		Shape* shape = getShapeless();
		Texture* texture = nullptr;

	public:
		bool hasTexture = false;

		Sprite() = default;
		Sprite(float x, float y);
		Sprite(float x, float y, Texture* texture);
		Sprite(float x, float y, Shape* shape);
		Sprite(float x, float y, Shape* shape, Texture* texture);
		Sprite(float x, float y, bool draw);
		Sprite(float x, float y, bool draw, Shape* shape);
	
		virtual ~Sprite();
		virtual float getX() const noexcept;
		virtual float getY() const noexcept;

		virtual void setDrawable(bool e) noexcept;
		virtual bool getDrawable() const noexcept; 
		
		virtual void setVisible(bool e) noexcept;
		virtual bool getVisible() const noexcept;

		virtual void setPosition(float x, float y);
		virtual glm::vec2 getPosition() const noexcept;
		
		virtual Shape* getShape() const noexcept;

		virtual Texture* getTexture() const noexcept;
		virtual void setTexture(Texture* texture) noexcept;
    };
	
	class VoidSprite : public Sprite
	{
	public:
		VoidSprite();
	};

}

#endif /* sge_object_h */
