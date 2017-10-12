set (DirectorSOURCES
	Director/sge_director.hpp
	Director/sge_director.cpp)

set (SceneSOURCES
	Scene/sge_scene.hpp
	Scene/sge_scene.cpp)

add_library (Scene SHARED
		${DirectorSOURCES}
		${SceneSOURCES})
