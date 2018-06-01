#ifndef sge_object_h
#define sge_object_h

#include <glm/vec2.hpp>
#include <GL/glew.h>
#include "../../Shape/sge_shape.hpp"
#include "../../Shape/sge_shapeless.hpp"

#include <sge_texture.hpp>

namespace SGE
{   
	class Object
	{   
	protected:
		float X = 0.f;
		float Y = 0.f;

		bool drawable = false;
		bool visible = false;
	
		Shape* shape = getShapeless();

		std::string path = "";

	public:
		bool hasTexture = false;

		Object() = default;
		Object(float x, float y);
		Object(float x, float y, Shape* shape);
		Object(float x, float y, bool draw);
		Object(float x, float y, bool draw, Shape* shape);
	
		virtual ~Object();

        GLTexture texture = {0,0,0};
	
        const char* path = nullptr;

		virtual float getX() const noexcept;
		virtual float getY() const noexcept;

		virtual void setDrawable(bool e) noexcept;
		virtual bool getDrawable() const noexcept; 
		
		virtual void setVisible(bool e) noexcept;
		virtual bool getVisible() const noexcept;

		virtual void setPosition(float x, float y);
		virtual glm::vec2 getPosition() const noexcept;
		
		virtual Shape* getShape() noexcept;

		const std::string& getPath() const;
    };
	
	class VoidObject : public Object
	{
	public:
		VoidObject();
	};

}

#endif /* sge_object_h */
