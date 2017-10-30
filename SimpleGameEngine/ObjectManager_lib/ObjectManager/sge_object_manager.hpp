#ifndef sge_object_manager_h
#define sge_object_manager_h

#include "sge_shader.hpp"
#include "sge_camera2d.hpp"
#include "sge_sprite_batch.hpp"
#include "sge_resource_manager.hpp"
#include "sge_input_manager.hpp"
#include "sge_fps_limiter.hpp"

#include "sge_relay.hpp"

#include <vector>
#include <map>
#include <stdexcept>
#include <ctime>

#include "sge_action_handler.hpp"
#include "sge_mouse.hpp"
#include "sge_level.hpp"
#include "sge_logic.hpp"
#include "sge_scene.hpp"

namespace SGE {
    
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

	    ObjectManager() noexcept;

	    bool init();

	    void addScene(SceneID s);

	    void deleteScene(SceneID s);

	    bool isOnScene();

	    void showScene(SceneID s);

	    void swapScene(SceneID s);

	    Level& getSceneData(SceneID s);

	    Camera2d* getCamera();


//        void registerCamera(Camera2d* c)
//        {
//            this->objects.emplace_back(this->getCameraID());
//        }
        
	public:
	    static ObjectManager* getManager();

	    Object* getObjectPtr(ObjectID id);

	    Scene* getScenePtr(SceneID id);

	    Logic* getLogicPtr(LogicID id);

	    void mapAction(const InputBinder& bind);

	    void unmapAction(const InputBinder& bind);

	    Action::ID addAction(Action* action);

	    Logic::ID addLogic(Logic* logic);

	    void interrupt();

	    Object::ID addObject(Object* o, std::string path = "");

	    Object::ID addObject(Object* o, Scene::ID s, std::string path = "");

	    void bindObject(Object::ID o, Scene::ID s);

	    void unbindObject(Object::ID o, Scene::ID s);

	    void update(ObjectID id, const Action& action);

	    void finalize();

	    void windowClosing();

	    ActionHandler* getActionHandler();

	    Object::ID getCameraID(void);

	    Object::ID getMouse(void);
    };
    
}

//Implementation of ObjectManager nested classes

#endif /* sge_object_manager_h */
