#ifndef sge_director_h
#define sge_director_h

#include <vector>
#include <memory>
#include "../../Logic/sge_logic.hpp"
#include "../../Scene/sge_scene.hpp"
#include "../../Utils/Logger/sge_logger.hpp"

namespace SGE
{

	/**
     * \brief 
     */
    class Director final
    {
		static std::shared_ptr<Logger> logger;
        static std::shared_ptr<LoggerError> logger_err;
	    /**
		 * \brief 
		 */
		Game* game = nullptr;
	    /**
		 * \brief 
		 */
		int Width = 0;
	    /**
		 * \brief 
		 */
		int Height = 0;

	    Scene* nextScene;

	    /**
	     * \brief 
	     * \param w 
	     * \param h 
	     */
	    Director(int w, int h);
	    /**
	     * \brief 
	     */
	    ~Director(); //Will prevent user form deleting Director, should be useful with ARC system in place.
		
	    /**
		 * \brief 
		 */
		std::vector<Scene*> scenes;

	public:
	    /**
	     * \brief 
	     * \param w 
	     * \param h 
	     * \return 
	     */
	    static Director* getDirector(int w = 0, int h = 0);

	    /**
	     * \brief 
	     * \return 
	     */
	    std::pair<int, int> getResolution();

	    /**
	     * \brief 
	     * \param scene 
	     * \return 
	     */
	    Scene* addScene(Scene* scene);

	    /**
	     * \brief 
	     * \param scene 
	     */
	    void deleteScene(Scene* scene);

	    /**
	     * \brief 
	     */
	    void finalize();

	    /**
	     * \brief Current Current way of connecting OM and Director
	     * \param pointer to Game Singleton
	     * \todo: Change this? Some Bootstraper perhaps?
	     */
	    void bindGame(Game* game);

	    Scene* getNextScene();
	    void setNextScene(Scene* next);

		void loadScene(Scene* scene);
		void unloadScene(Scene* scene);
		void resumeScene(Scene* scene);
		void suspendScene(Scene* scene);

		void toNextScene(Scene* scene);
    };
    
}

#endif /* sge_director_h */
