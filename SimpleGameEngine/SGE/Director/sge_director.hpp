#ifndef sge_director_h
#define sge_director_h

#include "../Scene/sge_scene.hpp"

namespace SGE {
	class Relay;

    class Director final{
	private:
		Director() {} 
		~Director(){} //Will prevent user form deleting Director, should be useful with ARC system in place.
		
	public:
		static Director* getDirector()
		{
			static Director* director = new Director();
			return director; //Can convert to ARC later.
		}

		Scene::ID addScene(Scene* s);
		void deleteScene(Scene::ID s);
		void showScene(Scene::ID s);
		void swapScene(Scene::ID s);
		void cleanUp();
    };
    
}

#endif /* sge_director_h */