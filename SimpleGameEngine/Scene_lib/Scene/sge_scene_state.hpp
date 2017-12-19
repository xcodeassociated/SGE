#ifndef SGE_SCENE_STATE_HPP
#define SGE_SCENE_STATE_HPP

namespace SGE
{
	enum class SceneState : int
	{
		Standby,
		Loading,
		Ready,
		Playing,
		Suspended
	};
}

#endif
