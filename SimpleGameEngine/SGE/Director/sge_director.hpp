#ifndef sge_director_h
#define sge_director_h

#include <vector>
#include <algorithm>
#include "../Relay/sge_relay_interface.hpp"

namespace SGE {
	class Relay;

    class Director final{
	private:
		Relay* relay = Relay::getRelay();

		Director() {} 
		~Director(){} //Will prevent user form deleting Director, should be useful with ARC system in place.
		
		std::vector<SceneID> scenes;

	public:
		static Director* getDirector()
		{
			static Director* director = new Director();
			return director; //Can convert to ARC later.
		}

		Scene::ID addScene(Scene* s) {
			SceneID id(relay->getNextCounter(),s);
			this->scenes.push_back(id);
			relay->relayScene(id);
			return id;
		}

		void deleteScene(Scene::ID s)
		{
			auto sceneIt = std::find(this->scenes.begin(), this->scenes.end(),s);
			if(sceneIt!=this->scenes.end())
			{
				this->scenes.erase(sceneIt);
				this->relay->relayDeleteScene(s);
				delete s.scene;
			}
		}

		void showScene(Scene::ID s)
		{

		}
		void swapScene(Scene::ID s);
		void cleanUp();
    };
    
}

#endif /* sge_director_h */