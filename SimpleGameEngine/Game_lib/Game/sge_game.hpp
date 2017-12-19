#ifndef sge_game_h
#define sge_game_h

#include <memory>
#include "sge_logger.hpp"

namespace SGE
{
    class Object;
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
    class MouseObject;

	/**
     * \brief 
     */
    class Game final
	{
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
        ResourceManager* resourceManager = nullptr;
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
	     * \return 
	     */
	    bool isOnScene() const;

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
		bool running = false;
        /**
         * \brief
         */
        float fps = 0;

        /**
         * \brief
         */
        void performActions();

        /**
         * \brief
         */
        void performLogics();

        /**
        * \brief
        */
        explicit Game();

        /**
         * \brief
         */
        void loop();

        /**
         * \brief
         */
        void stop();

        /**
         * \brief
         */
        void draw(Scene*);
        
	public:
		void run();

	    /**
	     * \brief 
	     * \return 
	     */
	    static Game* getGame();

		/**
		* \brief
		* \return
		*/
		bool init(float fps);

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
	     * \param o 
	     * \param path 
	     * \return 
	     */
	    Object* textureObject(Object* o, std::string path = "");

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
        MouseObject* getMouse();

	    /**
	     * \brief Current way of connecting OM and Director
	     * \param director pointer to Director Singleton
	     * \todo: Change this? Some Bootstraper perhaps?
	     */
	    void bindDirector(Director* director);
    };
    
}

#endif /* sge_game_h */
