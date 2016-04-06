#ifndef sge_object_h
#define sge_object_h

#include "../ID/sge_id.hpp"

namespace SGE {
	class ObjectManager;

	class ObjectID : public ID {
		Object* obj;

		Object* getObject() {
			return obj;
		}
	public:
		ObjectID(Object* o) : obj(o) {
		}
	};

    class Object{
	public:
		using ID = ObjectID;

		virtual void update()=0;
		virtual void draw()=0;
    };
    
}

#endif /* sge_object_h */