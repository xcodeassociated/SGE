#ifndef SGE_ACTION_HANDLER_HPP
#define SGE_ACTION_HANDLER_HPP

#include <vector>

namespace SGE
{
	enum class LogicPriority;
	class Action;
	class ActionBind;
	class ObjectBind;

	/**
     * \brief Workaround for std::hash not working with enums
     */
    struct KeyHash
	{
	    /**
         * \brief Returns undrlying value of enum
         * \tparam T Enum type
         * \param t Enum value
         * \return Numeric Enum Value
         */
        template <typename T>
	    std::size_t operator()(T t) const
		{
			return static_cast<std::size_t>(t);
		}
    };

	/**
	 * \brief Aliases std::hash<Key> or KeyHash when Key is enum
 	 * \tparam Key Checked value
	 */
	template <typename Key>
    using KeyHashAlias = typename std::conditional<std::is_enum<Key>::value, KeyHash, std::hash<Key>>::type;

	/**
     * \brief Handles the execution of actions
     */
    class ActionHandler
	{
	    /**
         * \brief Vector of queued ActionBinds
         */
        std::vector<ActionBind> actions;

	    /** 
	     * \brief Immediately executes Action a with objects b
	     * \param a Action ID
	     * \param b bound Objects
	     * \todo Do not perform all 3 action states at once!
	     */
	    void triggerAction(Action* a, const ObjectBind& b);

	    /**
	     * \brief Immediatel executes ActionBind's Action with it's Objects.
	     * \param b ActionBind
	     */
	    void triggerAction(const ActionBind& b);

    public:

	    /**
	     * \brief Constructs empty ActionHandler
	     */
	    ActionHandler();

	    /**
	     * \brief Executes Main part of the action received as result of user input
	     * \param bind Bound Action and Objects
	     */
	    void handleInputAction(ActionBind& bind);

	    /**
	     * \brief Executes Action begin and queues it
	     * \param bind Bound Action and Objects
	     */
	    void addAction(const ActionBind& bind);

	    /**
	     * \brief Executes queued actions, ending and deleting actions that have completed
	     */
	    void performAllActions();

	    /**
	     * \brief Immediately executes actions sent by Highest priority Logics, otherwise adds them to the queue.
	     * \param bind Bound Action and Objects
	     * \param priority Priority of Logic that sent this action.
	     */
	    void performSingleAction(const ActionBind& bind, LogicPriority priority);
    };

}

#endif // !SGE_ACTION_HANDLER_HPP
