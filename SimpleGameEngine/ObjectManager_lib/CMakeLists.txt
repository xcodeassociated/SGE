set (ObjectManagerSOURCES
	ObjectManager/sge_object_manager.hpp
	ObjectManager/sge_object_manager.cpp
	ObjectManager/tool/sge_camera_handler.hpp
	ObjectManager/tool/sge_camera_handler.cpp
	ObjectManager/tool/sge_game.hpp
	ObjectManager/tool/sge_game.cpp
	ObjectManager/tool/sge_input_handler.hpp
	ObjectManager/tool/sge_input_handler.cpp
	ObjectManager/tool/sge_renderer.hpp
	ObjectManager/tool/sge_renderer.cpp
	ObjectManager/tool/sge_window_manager.hpp
	ObjectManager/tool/sge_window_manager.cpp)


set (DirectorSOURCES
	Director/sge_director.hpp
	Director/sge_director.cpp)

	
add_library (ObjectManager SHARED
		${ObjectManagerSOURCES}
		${DirectorSOURCES})
		
	
target_link_libraries(ObjectManager
	Object
	Logic
	Utils
	IO
	Level
	Scene
	Renderer)	
