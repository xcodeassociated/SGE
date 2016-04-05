#ifndef sge_object_manager_h
#define sge_object_manager_h

#include "../Object/sge_object.hpp"
#include "../Action/sge_action.hpp"

namespace SGE {
    
    class ObjectManager final{
		
	public:
		static ObjectManager* getManager();
		Object::ID addObject(Object* o, Scene::ID s);
		void update(Object::ID id,const Action& action);
		void cleanUp();
    };
    
}

#endif /* sge_object_manager_h */