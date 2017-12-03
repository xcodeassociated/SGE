#ifndef sge_action_h
#define sge_action_h

#include "sge_object.hpp"
#include <initializer_list>


namespace SGE {
	class ObjectBind;
    class ActionBind;

	class Action{
    protected:
        double duration = 0;
		bool enabled = true;
		Action() = default;
		Action(double _d);
		Action(double _d, bool);

    public:
		using Binder = ActionBind;

		double getDuration() const;
		virtual ~Action() = default;

        virtual void action_begin(const ObjectBind& bind) = 0;
        virtual void action_main(const ObjectBind& bind) = 0;
        virtual void action_ends(const ObjectBind& bind) = 0;
        
    };

}
#endif /* sge_action_h */
