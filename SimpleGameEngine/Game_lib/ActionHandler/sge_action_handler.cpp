#include "sge_action_handler.hpp"
#include "sge_action.hpp"
#include <algorithm>

SGE::ActionHandler::ActionHandler(std::vector<Action*>& actions_referance) : actions(actions_referance)
{
}

void SGE::ActionHandler::setActionsReferance(std::vector<Action*>& actions_ref)
{
    this->actions = actions_ref;
}

void SGE::ActionHandler::triggerActionSingle(Action* action)
{
    action->action_begin();
    action->action_main();
    if (!action->isActive()) {
        action->action_ends();

        // release object locks
        auto objects = action->getObjects();
        if (objects.size() > 0)
        {
            for (auto object : objects)
            {
                if (object != nullptr)
                    object->setLock(LogicPriority::None);
            }
        }

        delete action;
    } else {
        this->addAction(action);
    }
}

void SGE::ActionHandler::triggerAction(Action* action)
{
    if (action->isActive())
    {
        action->action_begin();
        action->action_main();
    }
}

void SGE::ActionHandler::handleInputAction(Action* action)
{
	action->action_begin();
	action->action_main();
}

void SGE::ActionHandler::handleInputActionUnbind(Action* action)
{
    action->action_ends();
}

void SGE::ActionHandler::addAction(Action* a)
{
	this->actions.push_back(a);
}

void SGE::ActionHandler::remove_inactive_actions()
{
    auto last = std::remove_if(this->actions.begin(), this->actions.end(), [](const Action* action)
    {
        if (!action->isActive())
        {

            // release object locks
            auto objects = action->getObjects();
            if (objects.size() > 0)
            {
                for (auto object : objects)
                {
                    if (object != nullptr)
                        object->setLock(LogicPriority::None);
                }
            }

            delete action;
            return true;
        }
        return false;
    });
    this->actions.erase(last, this->actions.end());
}

void SGE::ActionHandler::performSingleAction(Action* action, LogicPriority priority)
{
	if (priority == LogicPriority::Highest)
	{
		this->triggerActionSingle(action);
	}
	else
	{
		this->addAction(action);

        // set object locks
        auto objects = action->getObjects();
        if (objects.size() > 0)
        {
            for (auto object : objects)
            {
                if (object != nullptr)
                    object->setLock(priority);
            }
        }
	}
}

std::vector<SGE::Action*>& SGE::ActionHandler::getActions()
{
    return this->actions;
}