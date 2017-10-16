set (DirectorSOURCES
	Director/sge_director.hpp
	Director/sge_director.cpp)

set (SceneSOURCES
	Scene/sge_scene.hpp
	Scene/sge_scene.cpp)

add_library (Scene SHARED
		${DirectorSOURCES}
		${SceneSOURCES})
if(WIN32)
	##Add dependencies
	target_link_libraries(Scene Object)
	##target_link_libraries(Scene ObjectManager)
	##target_link_libraries(Scene "../../lib/ObjectManager")
endif()
