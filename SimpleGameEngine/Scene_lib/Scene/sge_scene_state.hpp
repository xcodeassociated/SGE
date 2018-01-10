#ifndef SGE_SCENE_STATE_HPP
#define SGE_SCENE_STATE_HPP

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
}

#endif
