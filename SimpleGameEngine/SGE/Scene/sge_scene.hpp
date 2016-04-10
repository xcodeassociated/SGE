#ifndef sge_scene_h
#define sge_scene_h

#include "../ID/sge_id.hpp"

namespace SGE {
	
	class Scene;
	class Director;
	class ObjectManager;

	class SceneID final : public ID {
		friend class Director;
		friend class ObjectManager;

		Scene* scene;

	public:
		SceneID(const long id, Scene* s) : ID(id), scene(s) {};
	};

    class Scene{
	public:
		using ID = SceneID;

		virtual void onDraw()
		{

		}
    };
    
}

#endif /* sge_scene_h */