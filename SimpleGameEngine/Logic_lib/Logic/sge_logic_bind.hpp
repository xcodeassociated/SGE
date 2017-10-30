//
// Created by Janusz Majchrzak on 30/10/2017.
//

#ifndef SGE_ZOMBIEGAME_SGE_LOGIC_BIND_HPP
#define SGE_ZOMBIEGAME_SGE_LOGIC_BIND_HPP

#include "sge_logic_id.hpp"
#include "sge_object.hpp" // will be changed to: sge_object_bind.hpp

namespace SGE {

    class LogicBind
    {
        LogicID logic;
        ObjectBind bind;
    public:
        LogicBind(LogicID logic, Object::ID object);

        LogicID getLogic();

        ObjectBind& getObject();

        bool operator==(const LogicBind& b) const;

        bool operator<(const LogicBind& other) const;
    };

}


#endif //SGE_ZOMBIEGAME_SGE_LOGIC_BIND_HPP
