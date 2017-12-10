#ifndef sge_object_manager_h
#define sge_object_manager_h

#include <vector>
#include <map>
#include <stdexcept>
#include <ctime>
#include <string>
#include <memory>
#include "sge_resource_manager.hpp"
#include "sge_logger.hpp"

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
	class ResourceManager;
    class FpsLimiter;
	class Scene;
	class Logic;
	class Action;

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

		static std::shared_ptr<Logger> logger;
        static std::shared_ptr<LoggerError> logger_err;

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
	     * \return 
	     */
	    bool isOnScene();

	    /**
	     * \brief 
	     * \param s 
	     */
	    void showScene(Scene* s);

	    /**
	     * \brief 
	     * \param s 
	     */
	    void swapScene(Scene* s);

	    /**
	     * \brief 
	     * \param s 
	     * \return 
	     */
	    Level& getSceneData(Scene* s);

	    /**
	     * \brief 
	     * \return 
	     */

        /**
         * \brief
         */
        FpsLimiter* limiter = nullptr;
        /**
         * \brief
         */
        bool playing = false;
        /**
         * \brief
         */
        float time = 0;
        /**
         * \brief
         */
        float fps = 0;

        /**
         * \brief
         */
        void performActions(void);

        /**
         * \brief
         */
        void performLogics(void);

        /**
        * \brief
        */
        Game(ObjectManager *, ActionHandler *);

        /**
         * \brief
         */
        void run(void);

        /**
         * \brief
         */
        void stop(void);

        /**
         * \brief
         */
        void draw(void);

        /**
         * \brief
         */
        void setInputHandler(InputHandler *);
        
	public:
	    /**
	     * \brief 
	     * \return 
	     */
	    static Game* getGame();

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
	     */
	    void interrupt();

	    /**
	     * \brief 
	     * \param o 
	     * \param path 
	     * \return 
	     */
	    Object* addObject(Object* o, std::string path = "");

	    /**
	     * \brief 
	     * \param o 
	     * \param s 
	     * \param path 
	     * \return 
	     */
	    Object* addObject(Object* o, Scene* s, std::string path = "");

	    /**
	     * \brief 
	     * \param o 
	     * \param s 
	     */
	    void bindObject(Object* o, Scene* s);

	    /**
	     * \brief 
	     * \param o 
	     * \param s 
	     */
	    void unbindObject(Object* o, Scene* s);

	    /**
	     * \brief 
	     * \param id 
	     * \param action 
	     */
	    void update(Object* id, const Action& action);

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
		Camera2d* getCamera();

	    /**
	     * \brief 
	     * \return 
	     */
	    Object* getMouse(void);

	    /**
	     * \brief Current way of connecting OM and Director
	     * \param director pointer to Director Singleton
	     * \todo: Change this? Some Bootstraper perhaps?
	     */
	    void bindDirector(Director* director);
    };
    
}

#endif /* sge_object_manager_h */
