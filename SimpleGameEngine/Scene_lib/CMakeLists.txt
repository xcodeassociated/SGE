set (SceneSOURCES
	Scene/sge_scene.hpp
	Scene/sge_scene.cpp
	Scene/sge_scene_id.hpp
	Scene/sge_scene_id.cpp)

add_library (Scene SHARED
		${SceneSOURCES})

target_link_libraries(Scene 
	Object
	Level
	Logic)
