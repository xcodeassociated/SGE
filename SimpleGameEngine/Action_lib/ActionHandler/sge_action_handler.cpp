#include "sge_action_handler.hpp"
#include <algorithm>
#include "sge_action.hpp"
#include "sge_action_bind.hpp"

void SGE::ActionHandler::triggerAction(Action* a, const ObjectBind& b)
{
	a->action_begin(b);
	a->action_main(b);
	a->action_ends(b);
	delete a;
}

void SGE::ActionHandler::triggerAction(const ActionBind& b)
{
	this->triggerAction(const_cast<Action*>(b.getAction()), b.getBind());
}

SGE::ActionHandler::ActionHandler(): actions{}
{
}

void SGE::ActionHandler::handleInputAction(ActionBind& bind)
{
	//Currently will handle only main;
	bind.getAction()->action_main(bind.getBind());
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
		//TODO: do it in a object manager for all scene objects !!!
		//o->setLock(LogicPriority::None);
		act.getAction()->action_main(act.getBind());
	}
	auto last = std::remove_if(actions.begin(), actions.end(), [](const ActionBind& b)
                           {
	                           if (b.getAction()->getDuration() <= 0)
	                           {
		                           const_cast<Action*>(b.getAction())->action_ends(b.getBind());
		                           //if (b.getAction().getID() > 99L)
		                           {
			                           delete b.getAction(); //deletes managed action
		                           }
		                           return true;
	                           }
	                           return false;
                           }); //"removes" actions that ended.
	this->actions.erase(last, actions.end());//Actually removes managed actions that ended.
}

void SGE::ActionHandler::performSingleAction(const ActionBind& bind, LogicPriority priority)
{
	if (priority == LogicPriority::Highest)
	{
		this->triggerAction(bind);
	}
	else
	{
		//this->actions.push_back(bind);
		this->addAction(bind);
		//bind.first.getObject()->setLock(priority);
		for (Object& e : bind)
		{
			e.setLock(priority);
		}
	}
}
