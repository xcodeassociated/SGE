#ifndef sge_action_h
#define sge_action_h

#include "../ID/sge_id.hpp"

namespace SGE {
    class Object;
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
		ActionID(Action* a) : ID(-1L), action(a){}
		ActionID(long id, Action* a):
			ID(id),
			action(a)
		{}
	};

	class Action{
    protected:
        double duration = 0;
        ActionHandler* action_handler = nullptr;
        Action(double _d) : duration(_d) {};
        
    public:
		using ID = ActionID;

		double getDuration() const
		{
			return this->duration;
		}
		virtual ~Action() = default;
        virtual void action_begin(Object*) noexcept = 0;
        virtual void action_main(Object*) noexcept = 0;
        virtual void action_ends(Object*) noexcept = 0;

        virtual void setActionHandler(ActionHandler* _action_handler) noexcept
        {
            this->action_handler = _action_handler;
        };
        
    };
    
}
#endif /* sge_action_h */
