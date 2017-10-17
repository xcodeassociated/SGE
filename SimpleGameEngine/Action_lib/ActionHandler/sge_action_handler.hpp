#ifndef SGE_ACTION_HANDLER_HPP
#define SGE_ACTION_HANDLER_HPP

#include "sge_action.hpp"
//#include "sge_relay_interface.hpp"
#include <SDL2/SDL.h>

#include <vector>

namespace SGE{
	enum class Key
	{
		A = SDLK_a,
		B = SDLK_b,
		C = SDLK_c,
		D = SDLK_d,
		E = SDLK_e,
		F = SDLK_f,
		G = SDLK_g,
		H = SDLK_h,
		I = SDLK_i,
		J = SDLK_j,
		K = SDLK_k,
		L = SDLK_l,
		M = SDLK_m,
		N = SDLK_n,
		O = SDLK_o,
		P = SDLK_p,
		Q = SDLK_q,
		R = SDLK_r,
		S = SDLK_s,
		T = SDLK_t,
		U = SDLK_u,
		V = SDLK_v,
		W = SDLK_w,
		X = SDLK_x,
		Y = SDLK_y,
		Z = SDLK_z,

		n0 = SDLK_0,
		n1 = SDLK_1,
		n2 = SDLK_2,
		n3 = SDLK_3,
		n4 = SDLK_4,
		n5 = SDLK_5,
		n6 = SDLK_6,
		n7 = SDLK_7,
		n8 = SDLK_8,
		n9 = SDLK_9,

		F1 = SDLK_F1,
		F2 = SDLK_F2,
		F3 = SDLK_F3,
		F4 = SDLK_F4,
		F5 = SDLK_F5,
		F6 = SDLK_F6,
		F7 = SDLK_F7,
		F8 = SDLK_F8,
		F9 = SDLK_F9,
		F10 = SDLK_F10,
		F11 = SDLK_F11,
		F12 = SDLK_F12,
		F13 = SDLK_F13,
		F14 = SDLK_F14,
		F15 = SDLK_F15,
		F16 = SDLK_F16,
		F17 = SDLK_F17,
		F18 = SDLK_F18,
		F19 = SDLK_F19,
		F20 = SDLK_F20,
		F21 = SDLK_F21,
		F22 = SDLK_F22,
		F23 = SDLK_F23,
		F24 = SDLK_F24,

		Up = SDLK_UP,
		Down = SDLK_DOWN,
		Left = SDLK_LEFT,
		Right = SDLK_RIGHT,

		Return = SDLK_RETURN,
		Escape = SDLK_ESCAPE,
		Minus = SDLK_MINUS,
		Equals = SDLK_EQUALS,
		LeftBracket = SDLK_LEFTBRACKET,
		RightBracket = SDLK_RIGHTBRACKET,
		SemiColon = SDLK_SEMICOLON,
		Apostrophe = SDLK_QUOTE,
		Application = SDLK_APPLICATION,
		Copy = SDLK_COPY,
		Capslock = SDLK_CAPSLOCK,
		Comma = SDLK_COMMA,
		Period = SDLK_PERIOD,
		Tab = SDLK_TAB,
		Space = SDLK_SPACE,
		Backslash = SDLK_BACKSLASH,
		Slash = SDLK_SLASH,
		Separator = SDLK_SEPARATOR,
		PrintScreen = SDLK_PRINTSCREEN,
		ScrollLock = SDLK_SCROLLLOCK,
		Pause = SDLK_PAUSE,
		Insert = SDLK_INSERT,
		Home = SDLK_HOME,
		PageUp = SDLK_PAGEUP,
		PageDown = SDLK_PAGEDOWN,
		
		KP_Divide = SDLK_KP_DIVIDE,
		KP_Multiply= SDLK_KP_MULTIPLY,
		KP_Minus = SDLK_KP_MINUS,
		KP_Plus = SDLK_KP_PLUS,
		KP_Enter = SDLK_KP_ENTER,
		KP_0 = SDLK_KP_0,
		KP_1 = SDLK_KP_1,
		KP_2 = SDLK_KP_2,
		KP_3 = SDLK_KP_3,
		KP_4 = SDLK_KP_4,
		KP_5 = SDLK_KP_5,
		KP_6 = SDLK_KP_6,
		KP_7 = SDLK_KP_7,
		KP_8 = SDLK_KP_8,
		KP_9 = SDLK_KP_9,
		KP_Period = SDLK_KP_PERIOD,
//		KP_ = SDLK_KP_,

		BrightnessDown = SDLK_BRIGHTNESSDOWN,
		BrightnessUp = SDLK_BRIGHTNESSUP,
		VolumeUp = SDLK_VOLUMEUP,
		VolumeDown = SDLK_VOLUMEDOWN,


		AC_Back = SDLK_AC_BACK,
		AC_Bookmarks = SDLK_AC_BOOKMARKS,
		AC_Forward = SDLK_AC_FORWARD,
		AC_Home = SDLK_AC_HOME,
		AC_Refresh = SDLK_AC_REFRESH,
		AC_Search = SDLK_AC_SEARCH,
		AC_Stop = SDLK_AC_STOP,

		DisplaySwitch = SDLK_DISPLAYSWITCH,
		AltErase = SDLK_ALTERASE,
        
        MOUSE_LEFT_BUTTON = -10
	};
    
    struct KeyHash{
        template <typename T>
	    std::size_t operator()(T t) const
		{
			return static_cast<std::size_t>(t);
		}
    };

	template <typename Key>
    using KeyHashAlias = typename std::conditional<std::is_enum<Key>::value, KeyHash, std::hash<Key>>::type;
    
	class InputBinder{
		ActionBind bind;
		Key kid;

	public:
		InputBinder(std::initializer_list<ObjectID> object, Action::ID action, Key key);

		InputBinder(ObjectID object, Action::ID action, Key key);

		ActionBind getBind() const;

		Key getKey() const;
	};

    class ActionHandler {
        //Relay* relay = Relay::getRelay();
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
