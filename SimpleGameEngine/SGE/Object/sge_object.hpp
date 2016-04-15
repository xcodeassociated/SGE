#ifndef sge_object_h
#define sge_object_h

#include "../ID/sge_id.hpp"

namespace SGE {
	class ObjectManager;

	class ObjectID : public ID {
		friend class ObjectManager;
	public:
		ObjectID(const long id) : ID(id) {
		}
        ObjectID(const ObjectID&) = default;
        ObjectID& operator=(const ObjectID&) = default;
	};

    class Object{
    protected:
        float X;
        float Y;
        bool drawable = false;

	public:
        Object() = default;
        Object(float x, float y): X(x), Y(y){}
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
