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

set (ObjectRelaySOURCES
	Relay/sge_relay.hpp
	Relay/sge_relay.cpp
	Relay/sge_relay_interface.hpp
	Relay/sge_relay_interface.cpp)

add_library (ObjectManager SHARED
		${ObjectManagerSOURCES}
		${ObjectRelaySOURCES})
		
if(WIN32)
	##Add dependencies
	target_link_libraries(ObjectManager Object)
	target_link_libraries(ObjectManager Logic)
	target_link_libraries(ObjectManager Utils)
	target_link_libraries(ObjectManager IO)
	target_link_libraries(ObjectManager Level)
	target_link_libraries(ObjectManager Scene)
	target_link_libraries(ObjectManager Renderer)
endif()
