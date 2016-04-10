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
	};

    class Object{
	public:
		using ID = ObjectID;

		virtual void update()=0;
		virtual void draw()=0;
    };
    
}

#endif /* sge_object_h */