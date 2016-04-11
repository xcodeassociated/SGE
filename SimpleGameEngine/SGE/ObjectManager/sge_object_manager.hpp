#ifndef sge_object_manager_h
#define sge_object_manager_h

#include "../include/sge_include.hpp"
#include "../Shaders/sge_shader.hpp"
#include "../Camera2d/sge_camera2d.hpp"
#include "../SpriteBatch/SpriteBatch.hpp"
#include "../ResourceManager/sge_resource_manager.hpp"
#include "../TextureLoader/sge_glTexture.hpp"
#include "../InputManager/sge_input_manager.hpp"
#include "../Timing/sge_fps_limiter.hpp"

#include "../Relay/sge_relay_interface.hpp"

#include <initializer_list>
#include <algorithm>
#include <vector>
#include <map>
#include <stdexcept>

#include <random>
#include <ctime>

namespace SGE {
	class Object;
	class ObjectID;
	class Scene;
	class SceneID;
	class Action;
	class BackgroundElement;
	class WorldElement;

    class ObjectManager final{
		friend class Relay;

		//Declarations of nested classes
		class ActionHandler {

		};

		class Renderer {
			int width=0;
			int height=0;
			ObjectManager* oManager = nullptr;
			SpriteBatch* sceneBatch = nullptr;
			SpriteBatch* objecBatch = nullptr;
			ResourceManager* rManager = nullptr;
			Camera2d* camera = nullptr;
			SDL_Window* window = nullptr;
			Shader* shaderProgram = nullptr;
			std::vector<BackgroundElement>* background = nullptr;

		public:
			Renderer(std::pair<int, int> res, ObjectManager* m);
			void setBackground(std::vector<BackgroundElement>* b);
			void initResourceManager();
			void initShader();
			void initCamera();
			void spriteBatchInit();
			void createWindow();
			void showWindow();
			void finalizeWindow();
			void render();
			void renderLevel();
			void renderObjects();
		};

		class Game
		{
			ObjectManager* manager = nullptr;
			FpsLimiter* limiter = nullptr;
			bool playing = false;
			float time = 0, fps = 0;

		public:
			Game(ObjectManager* m);
			void run();
			void stop();
			void draw();
		};

	private:
		bool OnScene = false;
		long counter = 0;
		std::map<ObjectID, Object*> objects;
		std::map<SceneID, std::vector<ObjectID>> sceneObjects;

		Relay* relay = nullptr;
		Renderer* renderer = nullptr;
		Game* game = nullptr;

		ObjectManager() {
			this->relay = Relay::getRelay();
			this->relay->registerManager(this);
		}

		void addScene(SceneID s)
		{
			if (this->renderer == nullptr)
			{
				this->renderer = new Renderer(this->relay->relayGetResolution(), this);
				this->game = new Game(this);
			}
			this->sceneObjects.emplace(s,std::vector<ObjectID>());
		}

		void deleteScene(SceneID s)
		{
			if (this->sceneObjects.erase(s) != 0)
			{
				s.scene->finalize();
				delete s.scene;
			}
		}

		bool isOnScene()
		{
			return this->OnScene;
		}

		void showScene(SceneID s)
		{
			auto sceneObjectsIt = this->sceneObjects.find(s);
			if (sceneObjectsIt == this->sceneObjects.end()) throw std::runtime_error("Scene not Loaded");
			s.scene->onDraw();
			this->OnScene = true;

			this->renderer->createWindow();
			this->renderer->showWindow();

			this->renderer->initShader();
			this->renderer->initResourceManager();
			this->renderer->spriteBatchInit();
			this->renderer->initCamera();

			this->renderer->setBackground(&s.scene->getBackground());

			this->game->run();
		}

		void swapScene(SceneID s)
		{

		}
		
		std::vector<BackgroundElement>& getSceneData(SceneID s)
		{
			return s.scene->getBackground();
		}

	public:
		static ObjectManager* getManager(){
			static ObjectManager* manager = new ObjectManager();
			return manager; //Can be converted to ARC later.
		}

		void interrupt()
		{
			if (this->game)
			{
				this->game->stop();
			}
		}

		Object::ID addObject(Object* o)
		{
			ObjectID id(counter++);
			this->objects.insert(std::make_pair(id,o));
			return id;
		}

		Object::ID addObject(Object* o, Scene::ID s)
		{
			ObjectID id(counter++);
			this->objects.emplace(id, o);
			auto ObjectVectorIt = this->sceneObjects.find(s);
			if (ObjectVectorIt != this->sceneObjects.end())
			{
				ObjectVectorIt->second.emplace_back(id);
			}
			else
			{
				throw std::runtime_error("Scene does not exist"); //Todo: replace
			}
			return id;
		}
		
		void bindObject(Object::ID o, Scene::ID s) {
			auto ObjectVectorIt = this->sceneObjects.find(s);
			if (ObjectVectorIt != this->sceneObjects.end())
			{
				ObjectVectorIt->second.emplace_back(o);
			}
			else
			{
				throw std::runtime_error("Scene does not exist");
			}
		}

		void unbindObject(Object::ID o, Scene::ID s)
		{
			auto objectVectorIt = this->sceneObjects.find(s);
			if (objectVectorIt != this->sceneObjects.end())
			{
				auto objectIt = std::find(objectVectorIt->second.begin(), objectVectorIt->second.end(),o);
				if (objectIt != objectVectorIt->second.end())
				{
					objectVectorIt->second.erase(objectIt);
				}
			}
		}

		void update(ObjectID id,const Action& action);
		void finalize()
		{}
    };
    
}

//Implementation of ObjectManager nested classes
#include "sge_action_handler.hpp"
#include "sge_renderer.hpp"
#include "sge_game.hpp"

#endif /* sge_object_manager_h */
