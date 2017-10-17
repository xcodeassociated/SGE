#ifndef sge_action_h
#define sge_action_h

#include "sge_id.hpp"
#include "sge_object.hpp"
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
		ActionID(long id, Action* a);
	public:
		ActionID(Action* a);

		Action* getAction() const;

		Action* operator->() const;
	};

	class Action{
    protected:
        double duration = 0;
		bool enabled = true;
		Action() = default;
		Action(double _d);
		Action(double _d, bool);

    public:
		using ID = ActionID;
		using Binder = ActionBind;

		double getDuration() const;
		virtual ~Action() = default;

        virtual void action_begin(const ObjectBind& bind) = 0;
        virtual void action_main(const ObjectBind& bind) = 0;
        virtual void action_ends(const ObjectBind& bind) = 0;
        
    };
    
	class ActionBind {
		ObjectBind bind = ObjectBind();
        ActionID aid = ActionID(nullptr);
    public:
		ActionBind(const std::initializer_list<ObjectID>& object, Action::ID action);

		ActionBind(ObjectID object, ActionID action);
        ActionBind() = default;

		ObjectID* begin() const;

		ObjectID* end() const;

		ActionID getAction() const;

		const ObjectBind& getBind() const;

		std::size_t size() const;
    };
}
#endif /* sge_action_h */
