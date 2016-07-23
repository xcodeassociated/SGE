#ifndef sge_object_manager_h
#define sge_object_manager_h

#include "../include/sge_include.hpp"
#include "../Shaders/sge_shader.hpp"
#include "../Camera2d/sge_camera2d.hpp"
#include "../SpriteBatch/SpriteBatch.hpp"
#include "../ResourceManager/sge_resource_manager.hpp"
#include "../InputManager/sge_input_manager.hpp"
#include "../Timing/sge_fps_limiter.hpp"

#include "../Relay/sge_relay_interface.hpp"

#include <initializer_list>
#include <algorithm>
#include <vector>
#include <map>
#include <stdexcept>

#include <unordered_set>
#include <random>
#include <ctime>

namespace SGE {
	class Object;
	class ObjectID;
	class Scene;
	class SceneID;
	class Action;
	class ActionID;
	class BackgroundElement;
	class WorldElement;
    class Logic;
    
    class ObjectManager final{
		friend class Relay;
        friend class ActionHandler;
        
    private:
        class CameraHandler;
        class WindowManager;
        
		class Renderer {
			int width = 0, height = 0;
			ObjectManager* oManager = nullptr;
			SpriteBatch* sceneBatch = nullptr;
			SpriteBatch* objectBatch = nullptr;
            CameraHandler* camera_handler = nullptr;
			Shader* shaderProgram = nullptr;
            WindowManager* window_manager = nullptr;
			Scene* current = nullptr;
            
            void renderLevel(void);
            void renderObjects(void);
            
		public:
			Renderer(std::pair<int, int>, ObjectManager*, WindowManager*, CameraHandler*) noexcept;
			void initShader(void);
			void spriteBatchInit(void);
			void render(void);
		
		};
        
        class InputHandler;
		class Game{
			ObjectManager* manager = nullptr;
			FpsLimiter* limiter = nullptr;
			bool playing = false;
			float time = 0, fps = 0;
            InputHandler* input_handler = nullptr;
            ActionHandler* action_handler = nullptr;
            
            void processInputs(void); // Not used now - a candidate for deletion
            void performActions(void);
			void performLogics(void);
            
		public:
			Game(ObjectManager*, ActionHandler*);
			void run(void);
			void stop(void);
			void draw(void);
            void setInputHandler(InputHandler*);
		};
        
        class InputHandler{
            ObjectManager* manager = nullptr;
            InputManager* input_manager = nullptr;
			std::unordered_map<Key, ActionBind, KeyHashAlias<Key>> keyMap;
            
			void pressKey(Key k);

        public:
            InputHandler(ObjectManager*) noexcept;
            void operator()(void) noexcept;
			void mapAction(const InputBinder& bind);
			void unmapAction(const InputBinder& bind);
            
            class MouseHandler{
                MouseObject* mouse = nullptr;
               
            public:
                MouseHandler(void) noexcept;
                void setMouseCoords(glm::vec2 coords) noexcept;
                glm::vec2 getMouseCoords(void) const noexcept;
                MouseObject* getMouseObject(void) noexcept;
            };
            
        private:
            MouseHandler* mouseHandler = nullptr;
        public:
            MouseHandler* getMouseHandler() noexcept;
        };
        
        class WindowManager{
            ObjectManager* manager = nullptr;
            SDL_Window* window = nullptr;
            int width = 0, height = 0;
            
        public:
            WindowManager(std::pair<int, int>, ObjectManager*) noexcept;
            void createWindow(void);
            void showWindow(void) noexcept;
            void finalizeWindow(void) noexcept;
            SDL_Window* getWindow(void) noexcept;
        };
        
        class CameraHandler : public Object {
            Camera2d* camera = nullptr;
            ObjectManager* manager = nullptr;
            int x = 0, y = 0;
            double scale = .0f;
            
        public:
            CameraHandler(std::pair<int, int>, ObjectManager*) noexcept;
            Camera2d* getCamera();
            void setScale(double) noexcept;
            void setPosition(int, int) noexcept;
            void setPosition(glm::vec2) noexcept;
            void updateCamera(void) const noexcept;
            const glm::mat4& getCameraMatrix(void) const noexcept;
            glm::vec2 getScreenToWorld(glm::vec2) const noexcept;
            glm::vec2 getScreenToWorld(int, int) const noexcept;
            
        };

	private:
        ResourceManager* rManager = ResourceManager::getSingleton();
		bool OnScene = false;
		long counter = 100;
		std::vector<ObjectID> objects;
		std::map< SceneID, std::vector<ObjectID> > sceneObjects;

		Relay* relay = nullptr;
		Renderer* renderer = nullptr;
		Game* game = nullptr;
        InputHandler* input_handler = nullptr;
        WindowManager* window_manager = nullptr;
        CameraHandler* camera_handler = nullptr;
        ActionHandler* action_handler = nullptr;
		Scene* currentScene = nullptr;

        ObjectManager() noexcept : action_handler(new ActionHandler) {
			Logic::action_handler = this->action_handler;
			this->relay = Relay::getRelay();
			this->relay->registerManager(this);
		}
        
		bool init()
		{
			std::pair<int, int> resolution = this->relay->relayGetResolution();

			this->window_manager = new WindowManager(resolution, this);
            this->window_manager->createWindow();
            
			this->camera_handler = new CameraHandler(resolution, this);
			this->camera_handler->setPosition(this->camera_handler->getScreenToWorld(0, 0));
			this->camera_handler->setScale(.5f);

			this->renderer = new Renderer(resolution, this, this->window_manager, this->camera_handler);
           // this->renderer->initShader();
			this->game = new Game(this, this->action_handler);

			this->input_handler = new InputHandler(this);
			this->game->setInputHandler(this->input_handler);
			return true;
		}

		void addScene(SceneID s)
		{
		/*	if(this->renderer == nullptr)
			{
				this->init();
			}*/
			static bool init = this->init();
			this->sceneObjects.emplace(s, std::vector<ObjectID>());
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
			this->currentScene = s.scene;
			auto sceneObjectsIt = this->sceneObjects.find(s);
			if (sceneObjectsIt == this->sceneObjects.end()) throw std::runtime_error("Scene not Loaded");
            s.scene->BindObjects(&sceneObjectsIt->second);
            
			this->OnScene = true;

			//this->window_manager->createWindow();
			this->window_manager->showWindow();

			this->renderer->initShader();

			this->renderer->spriteBatchInit();

            s.scene->onDraw();
            
            this->game->run();

		}

		void swapScene(SceneID s)
		{
            //TODO
		}
		
		Level& getSceneData(SceneID s)
		{
			return s.scene->getLevel();
		}

        Camera2d* getCamera()
        {
            return this->camera_handler->getCamera();
        }
        
        
//        void registerCamera(Camera2d* c)
//        {
//            this->objects.emplace_back(this->getCameraID());
//        }
        
	public:
		static ObjectManager* getManager(){
			static ObjectManager* manager = new ObjectManager();
			return manager; //Can be converted to ARC later.
		}

        Object* getObjectPtr(ObjectID id)
        {
            return id.obj;
        }
        
        Scene* getScenePtr(SceneID id)
        {
            return id.scene;
        }
        
        Logic* getLogicPtr(LogicID id)
        {
            return id.logic;
        }
        
		void mapAction(const InputBinder& bind)
		{
			this->input_handler->mapAction(bind);
		}

		void unmapAction(const InputBinder& bind)
		{
			this->input_handler->unmapAction(bind);
		}

        Action::ID addAction(Action* action){
			return ActionID(this->counter++, action);
        }

		Logic::ID addLogic(Logic* logic)
		{
			return LogicID(this->counter++, logic);
		}
        
		void interrupt()
		{
			if (this->game)
			{
				this->game->stop();
			}
		}

        Object::ID addObject(Object* o, std::string path = "")
		{
			ObjectID id(counter++,o);
			this->objects.emplace_back(id);
            
            if(!path.empty()) o->texture = this->rManager->getTexture(path.c_str());
            
			return id;
		}

        Object::ID addObject(Object* o, Scene::ID s, std::string path = "")
		{
			ObjectID id(counter++,o);
			this->objects.emplace_back(id);
			auto ObjectVectorIt = this->sceneObjects.find(s);
			if (ObjectVectorIt != this->sceneObjects.end())
			{
				ObjectVectorIt->second.emplace_back(id);
			}
			else
			{
				throw std::runtime_error("Scene does not exist"); //Todo: replace
			}
            
            if(!path.empty()) o->texture = this->rManager->getTexture(path.c_str());
            
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

        void update(ObjectID id,const Action& action)
        {
            ;
        }
        
		void finalize()
		{
            ;
        }
        
        void windowClosing()
        {
            /* Handle window close action... */
            std::cerr << "SDL Window is trying to close!" << std::endl;
        }
        
        ActionHandler* getActionHandler(){
            return this->action_handler;
        }
        
        Object::ID getCameraID(void) {
            return ObjectID(0, this->camera_handler->getCamera());
        }
        
        Object::ID getMouse(void) {
            return ObjectID(1, this->input_handler->getMouseHandler()->getMouseObject());
        }
    };
    
}

//Implementation of ObjectManager nested classes
#include "tool/sge_window_manager.hpp"
#include "tool/sge_renderer.hpp"
#include "tool/sge_game.hpp"
#include "tool/sge_input_handler.hpp"
#include "tool/sge_camera_handler.hpp"

#endif /* sge_object_manager_h */
