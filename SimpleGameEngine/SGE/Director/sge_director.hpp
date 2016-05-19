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
		int Width = 0;
		int Height = 0;

		Director(int w, int h):relay(SGE::Relay::getRelay()), Width(w), Height(h) {
			this->relay->registerDirector(this);
		}
		~Director(){} //Will prevent user form deleting Director, should be useful with ARC system in place.
		
		std::vector<SceneID> scenes;

	public:
		static Director* getDirector(int w = 0, int h = 0)
		{
			static Director* director = new Director(w,h);
			return director; //Can convert to ARC later.
		}

		std::pair<int, int> getResolution()
		{
			return std::make_pair(this->Width, this->Height);
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
			}
		}

		void addLogicBinder(Scene::ID scene, Logic::Binder logic)
		{
			scene.scene->getLogics().push_back(logic);
            std::stable_sort(scene.scene->getLogics().begin(), scene.scene->getLogics().end());
		}

		void addLogicBinder(Scene::ID scene, Object::ID obj, Logic::ID logic)
		{
			this->addLogicBinder(scene,Logic::Binder(logic, obj));
		}

		void unbindLogic(Scene::ID scene, Object::ID obj, Logic::ID logic)
		{
			auto it = std::find(scene.scene->getLogics().begin(), scene.scene->getLogics().end(), Logic::Binder(logic, obj));
			if (it == scene.scene->getLogics().end()) return;
			scene.scene->getLogics().erase(it);
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

		void finalize()
		{}
    };
    
}

#endif /* sge_director_h */
