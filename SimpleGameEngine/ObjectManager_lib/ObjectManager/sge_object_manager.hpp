#ifndef sge_object_manager_h
#define sge_object_manager_h

#include "sge_relay.hpp"

#include <vector>
#include <map>
#include <stdexcept>
#include <ctime>

#include "sge_resource_manager.hpp"
#include "sge_action_handler.hpp"
#include "sge_level.hpp"
#include "sge_scene.hpp"

namespace SGE {

    class Game;
    class InputHandler;
    class Renderer;
    class WindowManager;
    class CameraHandler;
    class InputBinder;

    class ObjectManager final{
		friend class Relay;
        friend class ActionHandler;

        friend class Game;
        friend class InputHandler;
        friend class Renderer;

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
