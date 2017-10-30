//
// Created by Janusz Majchrzak on 30/10/2017.
//

#include "sge_logic_id.hpp"
#include "sge_id.hpp"


SGE::LogicID::LogicID(const long id, Logic* logic) : ID(id), logic(logic)
{
}

SGE::LogicID::LogicID(Logic* logic) : ID(-1L), logic(logic)
{
}

SGE::Logic* SGE::LogicID::getLogic() const
{
    return logic;
}

SGE::Logic* SGE::LogicID::operator->() const
{
    return logic;
}