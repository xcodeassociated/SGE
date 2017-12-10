#include "sge_key.hpp"
#include "sge_keyboard_state.hpp"
#include <SDL2/SDL.h>

bool SGE::isPressed(SGE::Key key)
{
	static const Uint8* const state = SDL_GetKeyboardState(nullptr);
	return state[SDL_GetScancodeFromKey(SDL_Keycode(key))];
}
