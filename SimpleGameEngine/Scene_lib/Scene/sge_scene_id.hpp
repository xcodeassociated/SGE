//
// Created by Janusz Majchrzak on 30/10/2017.
//

#ifndef SGE_ZOMBIEGAME_SGE_SCENE_ID_HPP
#define SGE_ZOMBIEGAME_SGE_SCENE_ID_HPP

#include "sge_id.hpp"

namespace SGE {

    class Scene;

    class SceneID final : public ID {
        friend class Director;
        friend class ObjectManager;

        Scene* scene;

    public:
        SceneID(const long id, Scene* s);
    };

}


#endif //SGE_ZOMBIEGAME_SGE_SCENE_ID_HPP
