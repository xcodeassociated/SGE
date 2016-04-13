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
		virtual ~Object() = 0;
		using ID = ObjectID;
    };
    
	Object::~Object(){}
}

#endif /* sge_object_h */
