//
// Created by Janusz Majchrzak on 30/10/2017.
//

#ifndef SGE_ZOMBIEGAME_SGE_LOGIC_ID_HPP
#define SGE_ZOMBIEGAME_SGE_LOGIC_ID_HPP

#include "sge_id.hpp"

namespace SGE {

    class Logic;

    class LogicID : public ID
    {
        friend class ObjectManager;
        friend class Logic;

        Logic* logic;
        LogicID(const long id, Logic* logic);
    public:
        LogicID(Logic* logic);

        Logic* getLogic() const;

        Logic* operator->() const;
    };

}


#endif //SGE_ZOMBIEGAME_SGE_LOGIC_ID_HPP
