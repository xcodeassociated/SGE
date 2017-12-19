set (SceneSOURCES
		Scene/sge_scene_state.hpp
		Scene/sge_scene.hpp
		Scene/sge_scene.cpp)

add_library (Scene SHARED
		${SceneSOURCES})

target_link_libraries(Scene 
		Object
		Level
		Logic
		Utils)
