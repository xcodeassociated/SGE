#ifndef sge_action_h
#define sge_action_h

#include "sge_object.hpp"
#include <initializer_list>
#include <vector>

namespace SGE
{
	class Action
	{
    protected:
        bool active = false;
		Action() = default;
		explicit Action(bool active);

    public:

		bool isActive() const;
		virtual ~Action() = default;

        virtual void action_begin() = 0;
        virtual void action_main() = 0;
        virtual void action_ends() = 0;
        virtual std::vector<Object*> getObjects() const = 0;
    };
}
#endif /* sge_action_h */
