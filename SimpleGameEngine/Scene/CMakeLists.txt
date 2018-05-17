set (SceneSOURCES
		sge_scene_state.hpp
		sge_scene.hpp
		sge_scene.cpp
		sge_box2dscene.hpp
		sge_box2dscene.cpp)

add_library (Scene
		${SceneSOURCES})

target_link_libraries(Scene 
		Object
		Level
		Logic
		Utils
		Box2D)

install(TARGETS Scene DESTINATION "${CMAKE_INSTALL_PREFIX}/lib")