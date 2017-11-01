#ifndef sge_scene_h
#define sge_scene_h

#include <vector>
#include <map>
#include "sge_level.hpp"
#include "sge_scene_id.hpp"
#include "sge_logic_bind.hpp"

namespace SGE {
	
	class Scene;
	class Director;
	class ObjectManager;


	/**
     * \brief 
     */
    class Scene{
	private:
	    /**
		 * \brief 
		 */
		using LogicVector = std::vector<LogicBind>;
	    /**
         * \brief 
         */
        using ObjectVector= std::vector<ObjectID>;
        
	    /**
		 * \brief 
		 */
		Level level;
	    /**
		 * \brief 
		 */
		LogicVector Logics;
	    /**
         * \brief 
         */
        ObjectVector* Objects = nullptr;

	public:
	    /**
		 * \brief 
		 */
		bool TextureLoaded = false;
	    /**
		 * \brief 
		 */
		using ID = SceneID;

	    /**
	     * \brief 
	     * \return 
	     */
	    LogicVector& getLogics();

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
	     * \param obj 
	     */
	    virtual void BindObjects(ObjectVector* obj) final;

	    /**
	     * \brief 
	     * \return 
	     */
	    virtual ObjectVector& getObjects() final;

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
