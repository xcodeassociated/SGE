set (SceneSOURCES
		Scene/sge_scene_state.hpp
		Scene/sge_scene.hpp
		Scene/sge_scene.cpp
		Scene/sge_box2dscene.hpp
		Scene/sge_box2dscene.cpp)

add_library (Scene SHARED
		${SceneSOURCES})

target_link_libraries(Scene 
		Object
		Level
		Logic
		Utils
		Box2D)
