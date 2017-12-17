#ifndef sge_scene_h
#define sge_scene_h

#include <vector>
#include <map>
#include "sge_level.hpp"
#include "sge_logic.hpp"

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
        using ObjectVector = std::vector<Object*>;
        using LogicVector = std::vector<Logic*>;
        using ActionVector = std::vector<Action*>;

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
	    virtual void loadLevel(const char* path, std::map<char, std::string> levelMask) final;

	    /**
	     * \brief 
	     * \return 
	     */
	    virtual Level& getLevel() final;

	    /**
	     * \brief 
	     * \return 
	     */
	    virtual ObjectVector& getObjects() final;

		void addObject(SGE::Object* object);

		void removeObject(SGE::Object* object);

		void addLogic(Logic* logic);

		void removeLogic(Logic* logic);

        void addAction(Action* action);

        void removeAction(Action* action);

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
