//
// Created by Janusz Majchrzak on 30/10/2017.
//

#ifndef SGE_ZOMBIEGAME_SGE_SCENE_ID_HPP
#define SGE_ZOMBIEGAME_SGE_SCENE_ID_HPP

#include "sge_id.hpp"

namespace SGE {

    class Scene;

	/**
     * \brief 
     * \todo Add missing access methods
	 */
    class SceneID final : public ID {
        friend class Director;
        friend class ObjectManager;

	    /**
         * \brief 
         */
        Scene* scene;

    public:
	    /**
         * \brief 
         * \param id 
         * \param s 
         */
        SceneID(const long id, Scene* s);
    };

}


#endif //SGE_ZOMBIEGAME_SGE_SCENE_ID_HPP
