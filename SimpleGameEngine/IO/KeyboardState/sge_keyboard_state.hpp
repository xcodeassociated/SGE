#ifndef sge_keyboard_state_hpp
#define sge_keyboard_state_hpp

namespace SGE
{
	enum class Key;
	/**
	 * \brief Checks whether given key is pressed.
	 * \param key Checked key enum
	 * \return True if given key is pressed, False otherwise
	 */
	bool isPressed(SGE::Key key);
}

#endif // !sge_keyboard_state_hpp
