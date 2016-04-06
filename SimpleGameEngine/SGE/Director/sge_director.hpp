#ifndef sge_director_h
#define sge_director_h

#include "../Scene/sge_scene.hpp"

namespace SGE {
	class Relay;

    class Director final{
		
	public:
		static Director* getDirector();
		Scene::ID addScene(Scene* s);
		void deleteScene(Scene::ID s);
		void showScene(Scene::ID s);
		void swapScene(Scene::ID s);
		void cleanUp();
    };
    
}

#endif /* sge_director_h */