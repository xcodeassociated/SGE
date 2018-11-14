#ifndef sge_game_h
#define sge_game_h

#include <memory>
#include "../Utils/Logger/sge_logger.hpp"

namespace SGE
{
    class Object;
	class Director;
    class Game;
    class InputHandler;
    class BatchRenderer;
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
		BatchRenderer* renderer = nullptr;
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
        std::string game_path = "";
		std::string shader_path = "";

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
	    void hide() const;
	    void unmapAll();
	    SGE::BatchRenderer* getRenderer() const
	    {
			return this->renderer;
	    }

	    /**
	     * \brief 
	     * \return 
	     */
	    static Game* getGame();

		/**
		* \brief
		* \return
		*/
		bool init(float fps, const std::string& glslPath);

		/**
		* \brief
		* \return
		*/
		void setGamePath(const std::string& path);
		void setShadersPath(const std::string& path);

		/**
		* \brief
		* \return
		*/
		const std::string& getGamePath() const;
	    const std::string& getShadersPath() const;

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
	    Object* textureObject(Object* o, const std::string& texture_file);

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
		Camera2d* getCamera() const;

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
