#ifndef SGE_ACTION_HANDLER_HPP
#define SGE_ACTION_HANDLER_HPP

#include "sge_action.hpp"
#include "sge_action_bind.hpp"
//#include "sge_relay_interface.hpp"

#include <vector>

namespace SGE{
    
    struct KeyHash{
        template <typename T>
	    std::size_t operator()(T t) const
		{
			return static_cast<std::size_t>(t);
		}
    };

	template <typename Key>
    using KeyHashAlias = typename std::conditional<std::is_enum<Key>::value, KeyHash, std::hash<Key>>::type;

    class ActionHandler {
        std::vector<ActionBind> actions;

	    void triggerAction(ActionID a, const ObjectBind& b);

	    void triggerAction(const ActionBind& b);

    public:

	    ActionHandler(void);

	    void handleInputAction(ActionBind& bind);

	    void addAction(ActionBind& bind);

	    void performAllActions();

	    void performSingleAction(const ActionBind& bind, LogicPriority priority);
    };

}

#endif // !SGE_ACTION_HANDLER_HPP
