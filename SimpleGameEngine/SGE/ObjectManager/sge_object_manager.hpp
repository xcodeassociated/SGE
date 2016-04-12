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
#include "sge_action_handler.hpp"

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
    
    class ObjectManager final{
		friend class Relay;
        
        
    private:
        class CameraHandler;
        class WindowManager;
        
		class Renderer {
			int width = 0, height = 0;
			ObjectManager* oManager = nullptr;
			SpriteBatch* sceneBatch = nullptr;
			SpriteBatch* objectBatch = nullptr;
			ResourceManager* rManager = nullptr;
            CameraHandler* camera_handler = nullptr;
			Shader* shaderProgram = nullptr;
			Level* level = nullptr;
            WindowManager* window_manager = nullptr;
            
            void renderLevel(void);
            void renderObjects(void);
            
		public:
			Renderer(std::pair<int, int>, ObjectManager*, WindowManager*, CameraHandler*) noexcept;
			void setLevel(Level*);
			void initResourceManager(void);
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
			std::unordered_map<Key, ActionBinder::Bind> keyMap;

			void pressKey(Key k);

        public:
            InputHandler(ObjectManager*) noexcept;
            void operator()(void) noexcept;
			void mapAction(const ActionBinder& bind);
			void unmapAction(const ActionBinder& bind);
        };
        
        class WindowManager{
            ObjectManager* manager = nullptr;
            SDL_Window* window = nullptr;
            int width = 0, height = 0;
            
        public:
            WindowManager(std::pair<int, int>, ObjectManager*) noexcept;
            void createWindow(void) noexcept;
            void showWindow(void) noexcept;
            void finalizeWindow(void) noexcept;
            SDL_Window* getWindow(void) noexcept;
        };
        
        class CameraHandler{
            Camera2d* camera = nullptr;
            ObjectManager* manager = nullptr;
            int x = 0, y = 0;
            double scale = .0f;
            
        public:
            CameraHandler(std::pair<int, int>, ObjectManager*) noexcept;
            void setScale(double) noexcept;
            void setPosition(int, int) noexcept;
            void setPosition(glm::vec2) noexcept;
            void updateCamera(void) const noexcept;
            const glm::mat4& getCameraMatrix(void) const noexcept;
            glm::vec2 getScreenToWorld(glm::vec2) const noexcept;
            glm::vec2 getScreenToWorld(int, int) const noexcept;
        };

	private:
		bool OnScene = false;
		long counter = 0;
		std::map< ObjectID, Object* > objects;
		std::map< SceneID, std::vector<ObjectID> > sceneObjects;

		Relay* relay = nullptr;
		Renderer* renderer = nullptr;
		Game* game = nullptr;
        InputHandler* input_handler = nullptr;
        WindowManager* window_manager = nullptr;
        CameraHandler* camera_handler = nullptr;
        ActionHandler* action_handler = nullptr;
        
        ObjectManager() noexcept : action_handler(new ActionHandler) {
			this->relay = Relay::getRelay();
			this->relay->registerManager(this);
		}
        
		void addScene(SceneID s)
		{
			if (this->renderer == nullptr)
			{
                std::pair<int, int> resolution = this->relay->relayGetResolution();
                
                this->window_manager = new WindowManager(resolution, this);
                
                this->camera_handler = new CameraHandler(resolution, this);
                this->camera_handler->setPosition( this->camera_handler->getScreenToWorld(0, 0) );
                this->camera_handler->setScale(.05f);
                
				this->renderer = new Renderer(resolution, this, this->window_manager, this->camera_handler);
				this->game = new Game(this, this->action_handler);
                
                this->input_handler = new InputHandler(this);
                this->game->setInputHandler(this->input_handler);
                
			}
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
			auto sceneObjectsIt = this->sceneObjects.find(s);
			if (sceneObjectsIt == this->sceneObjects.end()) throw std::runtime_error("Scene not Loaded");
			
			this->OnScene = true;

			this->window_manager->createWindow();
			this->window_manager->showWindow();

			this->renderer->initShader();
			this->renderer->initResourceManager();
			this->renderer->spriteBatchInit();
            
			this->renderer->setLevel( &(s.scene->getLevel()) );

            s.scene->onDraw();
            
            this->game->run();

		}

		void swapScene(SceneID s)
		{

		}
		
		Level& getSceneData(SceneID s)
		{
			return s.scene->getLevel();
		}

	public:
		static ObjectManager* getManager(){
			static ObjectManager* manager = new ObjectManager();
			return manager; //Can be converted to ARC later.
		}


		void mapAction(const ActionBinder& bind)
		{
			this->input_handler->mapAction(bind);
		}
		void unmapAction(const ActionBinder& bind)
		{
			this->input_handler->unmapAction(bind);
		}

        Action::ID addAction(Action* action){
			ActionID actionID(this->counter++, action);
			return actionID;
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
    };
    
}

//Implementation of ObjectManager nested classes
#include "tool/sge_window_manager.hpp"
#include "tool/sge_renderer.hpp"
#include "tool/sge_game.hpp"
#include "tool/sge_input_handler.hpp"
#include "tool/sge_camera_handler.hpp"

#endif /* sge_object_manager_h */
