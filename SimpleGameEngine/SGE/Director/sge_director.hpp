#ifndef sge_director_h
#define sge_director_h

#include <vector>
#include <algorithm>
#include <stdexcept>
#include "../Relay/sge_relay_interface.hpp"

namespace SGE {
	class Relay;

    class Director final{
	private:
		Relay* relay = nullptr;

		Director() {
			this->relay = SGE::Relay::getRelay();
			this->relay->registerDirector(this);
		}
		~Director(){} //Will prevent user form deleting Director, should be useful with ARC system in place.
		
		std::vector<SceneID> scenes;

	public:
		static Director* getDirector()
		{
			static Director* director = new Director();
			return director; //Can convert to ARC later.
		}

		Scene::ID addScene(Scene* scene) {
			SceneID id(relay->getNextCounter(),scene);
			this->scenes.push_back(id);
			relay->relayScene(id);
			return id;
		}

		void deleteScene(Scene::ID scene)
		{
			auto sceneIt = std::find(this->scenes.begin(), this->scenes.end(),scene);
			if(sceneIt!=this->scenes.end())
			{
				this->scenes.erase(sceneIt);
				this->relay->relayDeleteScene(scene);
				delete scene.scene;
			}
		}

		void showScene(Scene::ID scene)
		{
			if (!scene.scene->TextureLoaded)
			{
				throw std::runtime_error("You are an idiot");
			}
			this->relay->relayShowScene(scene);
		}

		void swapScene(Scene::ID scene)
		{
			if (!scene.scene->TextureLoaded)
			{
				throw std::runtime_error("You are an idiot");
			}
			this->relay->relaySwapScene(scene);
		}
		void cleanUp();
    };
    
}

#endif /* sge_director_h */