set (ActionSOURCES
		sge_action.hpp
		sge_action.cpp)

set (ActionsSources
		Actions/sge_action_move.hpp
		Actions/sge_action_move.cpp)


add_library(Action
		${ActionSOURCES}
		${ActionsSources})

target_link_libraries(Action
		Object
		Utils)

install(TARGETS Action DESTINATION "${CMAKE_INSTALL_PREFIX}/lib")