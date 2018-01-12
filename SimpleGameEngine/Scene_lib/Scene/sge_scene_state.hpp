#ifndef SGE_SCENE_STATE_HPP
#define SGE_SCENE_STATE_HPP
#include <string>

namespace SGE
{
	enum class SceneState : int
	{
		Standby,
		Ready,
		Playing,
		Suspended,
		Loading,
		Unloading,
		Resuming,
		Suspending
	};

	inline std::string toString(SceneState state)
	{
		switch(state)
		{
		case SceneState::Standby: return "Standby";
		case SceneState::Ready: return "Ready";
		case SceneState::Playing: return "Playing";
		case SceneState::Loading: return "Loading";
		case SceneState::Suspended: return "Suspended";
		case SceneState::Resuming: return "Resuming";
		case SceneState::Suspending: return "Suspending";
		case SceneState::Unloading: return "Unloading";
		default: return "";
		}
	}
}

#endif
