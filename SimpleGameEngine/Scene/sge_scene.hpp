#ifndef sge_scene_h
#define sge_scene_h

#include <vector>
#include <map>
#include "../Level/sge_level.hpp"
#include "../Logic/sge_logic.hpp"
#include "../Scene/sge_scene_state.hpp"

namespace SGE
{
	class Scene;
	class Director;

	/**
     * \brief 
     */
    class Scene
    {
	    /**
         * \brief 
         */
    public:
        using ObjectVector = std::vector<Object*>;
        using LogicVector = std::vector<Logic*>;
        using ActionVector = std::vector<Action*>;
    protected:
	    /**
		 * \brief 
		 */
		Level level;
	    /**
		 * \brief 
		 */
		LogicVector logics;
        /**
        * \brief
        */
        ActionVector actions;
	    /**
         * \brief 
         */
        ObjectVector objects;
	    
    public:
		unsigned long id = 0;
		SceneState state = SceneState::Standby;
	    /**
		 * \brief 
		 */
		bool TextureLoaded = false;

	    /**
	     * \brief 
	     * \return 
	     */
	    LogicVector& getLogics();

        ActionVector& getActions();

	    /**
		 * \brief 
		 */
		virtual ~Scene() = default;

	    /**
	     * \brief 
	     * \param path 
	     * \param levelMask 
	     */
	    virtual void loadLevel(const char* path, std::map<char, std::string> levelMask);

	    /**
	     * \brief 
	     * \return 
	     */
	    virtual Level& getLevel();

	    /**
	     * \brief 
	     * \return 
	     */
	    virtual ObjectVector& getObjects();

		virtual void addObject(SGE::Object* object);

		void removeObject(SGE::Object* object);

		void addLogic(Logic* logic);

		void removeLogic(Logic* logic);

        void addAction(Action* action);

        void removeAction(Action* action);

		virtual void loadScene();
		virtual void suspendScene();
		virtual void resumeScene();
		virtual void unloadScene();

		/**
		 * \brief 
		 */
		virtual void finalize() = 0;
	    /**
         * \brief 
         */
        virtual void onDraw() = 0;

    };
    
}

#endif /* sge_scene_h */
