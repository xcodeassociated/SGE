#ifndef sge_object_h
#define sge_object_h

#include <string>
#include <glm/vec2.hpp>
#include <GL/glew.h>
#include "sge_id.hpp"
#include "sge_shape.hpp"
#include "sge_shapeless.hpp"
#include "sge_logic_priority.hpp"
#include "sge_object_id.hpp"

namespace SGE {
	class ObjectManager;
	class Object;
        
    struct GLTexture {
        GLuint id;
        unsigned int width;
        unsigned int height;
    };

    
	class Object
	{
    private:
        
	protected:
		float X = 0.f;
		float Y = 0.f;
		bool drawable = false;
		Shape* shape = getShapeless();
		LogicPriority lock = LogicPriority::None;

	public:
		Object() = default;
		Object(float x, float y);
		Object(float x, float y, Shape* shape);
		Object(float x, float y, bool draw);
		Object(float x, float y, bool draw, Shape* shape);
		virtual ~Object() = 0;
		using ID = ObjectID;
        
        GLTexture texture = {0,0,0};
        const char* path = nullptr;

		virtual float& getX() noexcept final;

		virtual float& getY() noexcept final;

		virtual void setDrawable(bool e) noexcept final;

		virtual bool getDrawable(void) const noexcept final;

		virtual void setPosition(float x, float y);

		virtual glm::vec2 getPosition() const noexcept;

		virtual Shape* getShape(void) noexcept final;

		virtual LogicPriority getLock(void) const noexcept final;

		virtual void setLock(const LogicPriority lock) noexcept final;
    };
	
	class VoidObject : public Object {
	public:
		VoidObject();
	};

}

#endif /* sge_object_h */
