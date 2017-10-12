set (ActionSOURCES
	Action/sge_action.hpp
	Action/sge_action.cpp)

set (ActionsSources
	Action/Actions/sge_action_move.hpp
	Action/Actions/sge_action_move.cpp
	Action/Actions/sge_action_rotate.hpp
	Action/Actions/sge_action_rotate.cpp
	Action/Actions/sge_action_scale.hpp
	Action/Actions/sge_action_scale.cpp)

set (ActionHandlerSOURCES
	ActionHandler/sge_action_handler.hpp
	ActionHandler/sge_action_handler.cpp)

add_library(Action SHARED 
		${ActionSOURCES}
		${ActionsSources}
		${ActionHandlerSOURCES})
