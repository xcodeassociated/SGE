#ifndef sge_action_h
#define sge_action_h

#include "sge_id.hpp"
#include <initializer_list>

namespace SGE {
    class Object;
    class ObjectID;
	class ObjectBind;
    class ActionHandler;
	class ObjectManager;
	class Action;
	class ActionBind;
	

	class ActionID : public ID
	{
		friend class ActionHandler;
		friend class ObjectManager;

		Action* action = nullptr;
		ActionID(long id, Action* a) :
			ID(id),
			action(a)
		{}
	public:
		ActionID(Action* a) : ID(-1L), action(a){}
		Action* getAction() const
		{
			return this->action;
		}
		Action* operator->() const
		{
			return this->action;
		}
	};

	class Action{
    protected:
        double duration = 0;
		bool enabled = true;
		Action() = default;
        Action(double _d) : duration(_d) {};
		Action(double _d, bool ) : duration(_d) {};

    public:
		using ID = ActionID;
		using Binder = ActionBind;

		double getDuration() const
		{
			return this->duration;
		}
		virtual ~Action() = default;

        virtual void action_begin(const ObjectBind& bind) = 0;
        virtual void action_main(const ObjectBind& bind) = 0;
        virtual void action_ends(const ObjectBind& bind) = 0;
        
    };
    
	class ActionBind {
		ObjectBind bind = ObjectBind();
        ActionID aid = ActionID(nullptr);
    public:
		ActionBind(const std::initializer_list<ObjectID>& object, Action::ID action) : bind(object), aid(action) {}
        ActionBind(ObjectID object, ActionID action) : ActionBind({object}, action) {}
        ActionBind() = default;
        
        ObjectID* begin() const { return this->bind.begin(); }
        ObjectID* end() const { return this->bind.end(); }
        ActionID getAction() const { return this->aid; }
		const ObjectBind& getBind() const { return this->bind; }
        std::size_t size() const { return this->bind.size(); }
    };
}
#endif /* sge_action_h */
