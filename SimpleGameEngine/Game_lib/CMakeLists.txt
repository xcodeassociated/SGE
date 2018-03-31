set (GameSOURCES
		Game/sge_game.hpp
		Game/sge_game.cpp)

set (InputHandlerSOURCES
		InputHandler/sge_input_binder.hpp
		InputHandler/sge_input_binder.cpp
		InputHandler/sge_input_handler.hpp
		InputHandler/sge_input_handler.cpp)

set (DirectorSOURCES
		Director/sge_director.hpp
		Director/sge_director.cpp)

set (ActionHandlerSOURCES
		ActionHandler/sge_action_handler.hpp
		ActionHandler/sge_action_handler.cpp)

add_library (ActionHandler SHARED ${ActionHandlerSOURCES})

target_link_libraries(ActionHandler Action)

add_library (Game SHARED
		${GameSOURCES}
		${InputHandlerSOURCES}
		${DirectorSOURCES})
		
	
target_link_libraries(Game
		Object
		Utils
		IO
		Level
		Scene
		Renderer
		Utils
		ActionHandler)
