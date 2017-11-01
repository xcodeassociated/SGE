#ifndef sge_object_manager_h
#define sge_object_manager_h

#include <vector>
#include <map>
#include <stdexcept>
#include <ctime>
#include "sge_resource_manager.hpp"
#include "sge_scene_id.hpp"
#include "sge_action_id.hpp"
#include "sge_logic_id.hpp"


namespace SGE {

	class Director;
    class Game;
    class InputHandler;
    class Renderer;
    class WindowManager;
    class CameraHandler;
    class InputBinder;
	class Level;
	class Camera2d;
	class ActionHandler;

    class ObjectManager final{
        friend class ActionHandler;
		friend class Director;
        friend class Game;
        friend class InputHandler;
        friend class Renderer;

	private:
        ResourceManager* rManager = ResourceManager::getSingleton();
		bool OnScene = false;
		long counter = 100;
		std::vector<ObjectID> objects;
		std::map< SceneID, std::vector<ObjectID> > sceneObjects;

		Director* director = nullptr;
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

	    ActionID addAction(Action* action);

	    LogicID addLogic(Logic* logic);

	    void interrupt();

	    ObjectID addObject(Object* o, std::string path = "");

	    ObjectID addObject(Object* o, SceneID s, std::string path = "");

	    void bindObject(ObjectID o, SceneID s);

	    void unbindObject(ObjectID o, SceneID s);

	    void update(ObjectID id, const Action& action);

	    void finalize();

	    void windowClosing();

	    ActionHandler* getActionHandler();

	    Object::ID getCameraID(void);

	    Object::ID getMouse(void);

	    /**
	     * \brief Current way of connecting OM and Director
	     * \param director pointer to Director Singleton
	     * \todo: Change this? Some Bootstraper perhaps?
	     */
	    void bindDirector(Director* director);
    };
    
}

//Implementation of ObjectManager nested classes

#endif /* sge_object_manager_h */
