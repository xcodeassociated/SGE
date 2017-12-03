set (ActionSOURCES
	Action/sge_action.hpp
	Action/sge_action.cpp
	Action/sge_action_bind.hpp
	Action/sge_action_bind.cpp)

set (ActionsSources
	Action/Actions/sge_action_move.hpp
	Action/Actions/sge_action_move.cpp
	Action/Actions/sge_action_rotate.hpp
	Action/Actions/sge_action_rotate.cpp
	Action/Actions/sge_action_scale.hpp
	Action/Actions/sge_action_scale.cpp)

set (ActionHandlerSOURCES
	ActionHandler/sge_action_handler.hpp
	ActionHandler/sge_action_handler.cpp
	ActionHandler/sge_input_binder.hpp
	ActionHandler/sge_input_binder.cpp
	ActionHandler/sge_action_handler.hpp
	ActionHandler/sge_key.hpp)

add_library(Action SHARED 
		${ActionSOURCES}
		${ActionsSources}
		${ActionHandlerSOURCES})
target_link_libraries(Action Object)
