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

	/**
     * \brief 
     */
    class ObjectManager final{
	    /**
         * \brief 
         */
        friend class ActionHandler;
	    /**
		 * \brief 
		 */
		friend class Director;
	    /**
         * \brief 
         */
        friend class Game;
	    /**
         * \brief 
         */
        friend class InputHandler;
	    /**
         * \brief 
         */
        friend class Renderer;

	private:
	    /**
         * \brief 
         */
        ResourceManager* rManager = ResourceManager::getSingleton();
	    /**
		 * \brief 
		 */
		bool OnScene = false;
	    /**
		 * \brief 
		 */
		long counter = 100;
	    /**
		 * \brief 
		 */
		std::vector<ObjectID> objects;
	    /**
		 * \brief 
		 */
		std::map< SceneID, std::vector<ObjectID> > sceneObjects;

	    /**
		 * \brief 
		 */
		Director* director = nullptr;
	    /**
		 * \brief 
		 */
		Renderer* renderer = nullptr;
	    /**
		 * \brief 
		 */
		Game* game = nullptr;
	    /**
         * \brief 
         */
        InputHandler* input_handler = nullptr;
	    /**
         * \brief 
         */
        WindowManager* window_manager = nullptr;
	    /**
         * \brief 
         */
        CameraHandler* camera_handler = nullptr;
	    /**
         * \brief 
         */
        ActionHandler* action_handler = nullptr;
	    /**
		 * \brief 
		 */
		Scene* currentScene = nullptr;

	    /**
	     * \brief 
	     */
	    ObjectManager() noexcept;

	    /**
	     * \brief 
	     * \return 
	     */
	    bool init();

	    /**
	     * \brief 
	     * \param s 
	     */
	    void addScene(SceneID s);

	    /**
	     * \brief 
	     * \param s 
	     */
	    void deleteScene(SceneID s);

	    /**
	     * \brief 
	     * \return 
	     */
	    bool isOnScene();

	    /**
	     * \brief 
	     * \param s 
	     */
	    void showScene(SceneID s);

	    /**
	     * \brief 
	     * \param s 
	     */
	    void swapScene(SceneID s);

	    /**
	     * \brief 
	     * \param s 
	     * \return 
	     */
	    Level& getSceneData(SceneID s);

	    /**
	     * \brief 
	     * \return 
	     */
	    Camera2d* getCamera();
        
	public:
	    /**
	     * \brief 
	     * \return 
	     */
	    static ObjectManager* getManager();

	    Object* getObjectPtr(ObjectID id);

	    Scene* getScenePtr(SceneID id);

	    Logic* getLogicPtr(LogicID id);

	    /**
	     * \brief 
	     * \param bind 
	     */
	    void mapAction(const InputBinder& bind);

	    /**
	     * \brief 
	     * \param bind 
	     */
	    void unmapAction(const InputBinder& bind);

	    /**
	     * \brief 
	     * \param action 
	     * \return 
	     */
	    ActionID addAction(Action* action);

	    /**
	     * \brief 
	     * \param logic 
	     * \return 
	     */
	    LogicID addLogic(Logic* logic);

	    /**
	     * \brief 
	     */
	    void interrupt();

	    /**
	     * \brief 
	     * \param o 
	     * \param path 
	     * \return 
	     */
	    ObjectID addObject(Object* o, std::string path = "");

	    /**
	     * \brief 
	     * \param o 
	     * \param s 
	     * \param path 
	     * \return 
	     */
	    ObjectID addObject(Object* o, SceneID s, std::string path = "");

	    /**
	     * \brief 
	     * \param o 
	     * \param s 
	     */
	    void bindObject(ObjectID o, SceneID s);

	    /**
	     * \brief 
	     * \param o 
	     * \param s 
	     */
	    void unbindObject(ObjectID o, SceneID s);

	    /**
	     * \brief 
	     * \param id 
	     * \param action 
	     */
	    void update(ObjectID id, const Action& action);

	    /**
	     * \brief 
	     */
	    void finalize();

	    /**
	     * \brief 
	     */
	    void windowClosing();

	    /**
	     * \brief 
	     * \return 
	     */
	    ActionHandler* getActionHandler();

	    /**
	     * \brief 
	     * \return 
	     */
	    Object::ID getCameraID(void);

	    /**
	     * \brief 
	     * \return 
	     */
	    Object::ID getMouse(void);

	    /**
	     * \brief Current way of connecting OM and Director
	     * \param director pointer to Director Singleton
	     * \todo: Change this? Some Bootstraper perhaps?
	     */
	    void bindDirector(Director* director);
    };
    
}

#endif /* sge_object_manager_h */
