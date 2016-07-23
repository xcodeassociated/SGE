#ifndef sge_object_h
#define sge_object_h

#include "../ThirdParty_Librarys/glm/vec2.hpp" //Forgot to include it before. 
#include "../ID/sge_id.hpp"
#include "Shape/sge_shape.hpp"

namespace SGE {
	class ObjectManager;
	class Object;
        
    struct GLTexture {
        GLuint id;
        unsigned int width;
        unsigned int height;
    };
    
	enum class LogicPriority
	{
		Highest = 0,
		High,
		Mid,
		Low,
		None
	};

	class ObjectID : public ID {
		friend class ObjectManager;
		Object* obj = nullptr;
	public:
		ObjectID(const long id) : ID(id) {
		}
		ObjectID(const long id, Object* o) : ID(id), obj(o) {
		}
        ObjectID() : ID(0) {}
		Object* getObject() const
		{
			return this->obj;
		}

        ObjectID(const ObjectID&) = default;
        ObjectID& operator=(const ObjectID&) = default;
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
		Object(float x, float y) : X(x), Y(y){}
        Object(float x, float y, Shape* shape): X(x), Y(y), shape(shape){}
		Object(float x, float y, bool draw) : X(x), Y(y), drawable(draw){}
		Object(float x, float y, bool draw, Shape* shape) : X(x), Y(y), drawable(draw), shape(shape){}
		virtual ~Object() = 0;
		using ID = ObjectID;
        
        GLTexture texture = {0,0,0};
        const char* path = nullptr;
        
        virtual float& getX() noexcept final
        {
            return this->X;
        }
        
        virtual float& getY() noexcept final
        {
            return this->Y;
        }
        
        virtual void setDrawable(bool e) noexcept final{
            this->drawable = e;
        }
        
        virtual bool getDrawable(void) const noexcept final {
            return this->drawable;
        }
        
        virtual void setPosition(float x, float y){
            this->X=x;
            this->Y=y;
        }
        
		virtual glm::vec2 getPosition() const noexcept
		{
			return glm::vec2(this->X, this->Y);
		}

        virtual Shape* getShape(void) noexcept final {
            return this->shape;
        }

		virtual LogicPriority getLock(void) const noexcept final
		{
			return lock;
		}

		virtual void setLock(const LogicPriority lock) noexcept final
		{
			this->lock = lock;
		}
    };

	inline Object::~Object()
	{
		if(this->shape->isDisposable()) delete this->shape;
	}
	
	class VoidObject : public Object {
	public:
		VoidObject() :Object() {};
	};
}

#endif /* sge_object_h */
