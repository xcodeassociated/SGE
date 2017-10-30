//
// Created by Janusz Majchrzak on 30/10/2017.
//

#include "sge_logic_bind.hpp"
#include "sge_logic.hpp"

SGE::LogicBind::LogicBind(LogicID logic, Object::ID object): logic(logic), bind(object)
{
}

SGE::LogicID SGE::LogicBind::getLogic()
{
    return this->logic;
}

SGE::ObjectBind& SGE::LogicBind::getObject()
{
    return this->bind;
}

bool SGE::LogicBind::operator==(const LogicBind& b) const
{
    return logic == b.logic && bind[0] == b.bind[0];
}

bool SGE::LogicBind::operator<(const LogicBind& other) const
{
    if (bind[0].getID() == other.bind[0].getID())
    {
        return this->logic->getPriority() < other.logic->getPriority();
    }
    return bind[0].getID() < other.bind[0].getID();
}
