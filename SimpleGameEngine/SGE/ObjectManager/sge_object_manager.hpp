#ifndef sge_object_manager_h
#define sge_object_manager_h

namespace SGE {
	class Object;
	class ObjectID;
	class Scene;
	class SceneID;
	class Action;

	class Relay;

    class ObjectManager final{
		
	public:
		static ObjectManager* getManager();
		typename ObjectID addObject(Object* o, SceneID s);
		void addScene(SceneID id);
		void update(ObjectID id,const Action& action);
		void cleanUp();
    };
    
}

#endif /* sge_object_manager_h */
