#ifndef sge_action_h
#define sge_action_h

#include "sge_object.hpp"
#include <initializer_list>


namespace SGE
{
	class ObjectBind;
    class ActionBind;

	class Action
	{
    protected:
        bool active = false;
		Action() = default;
		Action(bool active);

    public:
		using Binder = ActionBind;

		bool isActive() const;
		virtual ~Action() = default;

        virtual void action_begin(const ObjectBind& bind) = 0;
        virtual void action_main(const ObjectBind& bind) = 0;
        virtual void action_ends(const ObjectBind& bind) = 0;
        
    };

}
#endif /* sge_action_h */
