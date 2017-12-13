#include "sge_action_handler.hpp"
#include <algorithm>
#include "sge_action.hpp"
#include "sge_action_bind.hpp"

#include <iostream>
void SGE::ActionHandler::triggerAction(Action* a, const ObjectBind& b)
{
	a->action_begin(b);
	a->action_main(b);
	if (!a->isActive())
	{
		a->action_ends(b);
		delete a;
	}
    else
    {
        this->addAction({b[0], a});
    }

}

void SGE::ActionHandler::triggerAction(const ActionBind& b)
{
	this->triggerAction(const_cast<Action*>(b.getAction()), b.getBind());
}

SGE::ActionHandler::ActionHandler() : actions{}
{
}

void SGE::ActionHandler::handleInputAction(ActionBind& bind)
{
	bind.getAction()->action_begin(bind.getBind());
	bind.getAction()->action_main(bind.getBind());
}

void SGE::ActionHandler::handleInputActionUnbind(ActionBind& bind)
{
    bind.getAction()->action_ends(bind.getBind());
}

void SGE::ActionHandler::addAction(const ActionBind& bind)
{
	const_cast<Action*>(bind.getAction())->action_begin(bind.getBind());
	this->actions.push_back(bind);
}

void SGE::ActionHandler::performAllActions()
{
	for (ActionBind& act : this->actions)
	{
        act.getAction()->action_begin(act.getBind());
        act.getAction()->action_main(act.getBind());
	}
	auto last = std::remove_if(actions.begin(), actions.end(), [](const ActionBind& b)
       {
           if (!b.getAction()->isActive())
           {
               const_cast<Action*>(b.getAction())->action_ends(b.getBind());
               {
                   delete b.getAction();
               }
               return true;
           }
           return false;
       });
	this->actions.erase(last, actions.end());
}

void SGE::ActionHandler::performSingleAction(const ActionBind& bind, LogicPriority priority)
{
	if (priority == LogicPriority::Highest)
	{
		this->triggerAction(bind);
	}
	else
	{
		this->addAction(bind);
		for (Object* e : bind)
		{
			e->setLock(priority);
		}
	}
}
