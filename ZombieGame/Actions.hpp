#ifndef ZOMBIEGAME_ACTIONS
#define ZOMBIEGAME_ACTIONS

#include <sge_action.hpp>
#include <sge_logic.hpp>
#include <sge_mouse.hpp>
#include "sge_game.hpp"


class GOTO : public SGE::Action
{
	SGE::Object* object = nullptr;

public:
	GOTO(SGE::Object* object);

	virtual void action_begin() noexcept override;

	virtual void action_main() noexcept override;

	virtual void action_ends() noexcept override;
};

class PortalAction : public SGE::Action
{
public:
	PortalAction();

	virtual void action_begin() override;

	virtual void action_main() override;

	virtual void action_ends() override;
};

class LogicSwitch : public SGE::Action
{
	SGE::Logic* logic = nullptr;

public:
	LogicSwitch(SGE::Logic* id);

	void action_begin() override;

	void action_main() override;

	void action_ends() override;
};

class MouseClickedAction : public SGE::Action
{
	SGE::MouseObject* mouseObject = nullptr;
	SGE::Object* player = nullptr;

public:
	MouseClickedAction(SGE::MouseObject* mouseObject, SGE::Object* player);

	virtual void action_begin() noexcept override;

	virtual void action_ends() noexcept override;

	virtual void action_main() noexcept override;
};

class Load : public SGE::Action
{
	SGE::Scene* nextScene = nullptr;
public:
	explicit Load(SGE::Scene* scene);
	void action_begin() override;
	void action_main() override;
	void action_ends() override;
	
};

#endif
