#ifndef sge_scene_h
#define sge_scene_h

#include "../ID/sge_id.hpp"

namespace SGE {
	
	class Director;

	class SceneID final : public ID {
		friend class director;
		Scene* scene = nullptr;

		Scene* getScene() {
			return scene;
		}
	public:
		SceneID(Scene* s) : scene(s) {};
	};

    class Scene{
	public:
		using ID = SceneID;
    };
    
}

#endif /* sge_scene_h */