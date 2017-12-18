#ifndef SGE_ACTION_HANDLER_HPP
#define SGE_ACTION_HANDLER_HPP

#include <vector>

namespace SGE
{
	enum class LogicPriority;
	class Action;

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
         * \brief Vector of queued Action pointers
         */
        std::vector<Action*>* actions;

	public:

	    /**
	     * \brief Constructs empty ActionHandler
	     */
	    explicit ActionHandler();

	    /**
	     * \brief Immediately executes actions sent by Highest priority Logics, otherwise adds them to the queue.
	     * \param bind Bound Action and Objects
	     * \param priority Priority of Logic that sent this action.
	     */
	    void performSingleAction(Action* action, LogicPriority priority);

		void setActions(std::vector<Action*>& actionsVec); //TODO: this method has tobe triggered when swapping scene

		/**
		* \brief Immediately executes Action a with objects b
		* \param action Action pointer
		*/
		void triggerActionSingle(Action* action);

		void addAction(Action* action);

		std::vector<Action*>& getActions();

	};

}

#endif // !SGE_ACTION_HANDLER_HPP
