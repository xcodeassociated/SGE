#ifndef sge_object_h
#define sge_object_h

#include "../ID/sge_id.hpp"

namespace SGE {
	class ObjectManager;
	class Object;

	enum class Shape : char{
		Circle,
		Rectangle,
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

		Object* getObject() const
		{
			return this->obj;
		}

        ObjectID(const ObjectID&) = default;
        ObjectID& operator=(const ObjectID&) = default;
	};

    class Object{
    protected:
        float X;
        float Y;
        bool drawable = false;
		Shape shape = Shape::None;

	public:
		Object() = default;
        Object(float x, float y, Shape s = Shape::None): X(x), Y(y), shape(s){}
		Object(float x, float y, bool draw, Shape s = Shape::None) : X(x), Y(y), drawable(draw), shape(s){}
		virtual ~Object() = 0;
		using ID = ObjectID;
        
        virtual float& getX() final
        {
            return this->X;
        }
        
        virtual float& getY() final
        {
            return this->Y;
        }
        
        virtual void setDrawable(bool e) final{
            this->drawable = e;
        }
        
        virtual bool getDrawable(void) const final {
            return this->drawable;
        }
        
        virtual void setPosition(float x, float y){
            this->X=x;
            this->Y=y;
        }
    };
    
	Object::~Object(){}
}

#endif /* sge_object_h */
