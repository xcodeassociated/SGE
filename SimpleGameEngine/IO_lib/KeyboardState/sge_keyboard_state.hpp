#ifndef sge_keyboard_state_hpp
#define sge_keyboard_state_hpp

namespace SGE
{
	bool isPressed(SGE::Key key)
	{
		static const Uint8* const state = SDL_GetKeyboardState(nullptr);
		return state[SDL_GetScancodeFromKey(SDL_Keycode(key))];
	}
}

#endif // !sge_keyboard_state_hpp
