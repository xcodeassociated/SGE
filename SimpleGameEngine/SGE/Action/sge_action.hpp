#ifndef sge_action_h
#define sge_action_h

#include "../ID/sge_id.hpp"

namespace SGE {
    class ActionHandler;
	class Action;

	class ActionID : public ID
	{
		friend class ActionHandler;

		Action* action = nullptr;

		Action* getAction() const
		{
			return this->action;
		}
	public:
		ActionID(long id, Action* a):
			ID(id),
			action(a)
		{}
	};

	class Action{
    protected:
        double duration = 0;
        ActionHandler* action_handler = nullptr;
        
    public:
		using ID = ActionID;

        virtual void action_begin(void) noexcept = 0;
        virtual void action_main(void) noexcept = 0;
        virtual void action_ends(void) noexcept = 0;

        virtual void setObjectManager(ActionHandler*) noexcept = 0;
        
    };
    
}
#endif /* sge_action_h */