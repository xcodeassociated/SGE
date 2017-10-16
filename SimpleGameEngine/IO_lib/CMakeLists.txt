set (IOSOURCES_InputManager
	InputManager/sge_input_manager.hpp
	InputManager/sge_input_manager.cpp)

set (IOSOURCES_IOManager
	IOManager/sge_io_manager.hpp
	IOManager/sge_io_manager.cpp)

set (IOSOURCES_KeyboardState
	KeyboardState/sge_keyboard_state.hpp
	KeyboardState/sge_keyboard_state.cpp)

set (IOSOURCES_Mouse
	Mouse/sge_mouse.hpp
	Mouse/sge_mouse.cpp)

add_library(IO SHARED 
		${IOSOURCES_InputManager}
		${IOSOURCES_IOManager}
		${IOSOURCES_KeyboardState}
		${IOSOURCES_Mouse})
if(WIN32)
	##Add dependencies
	target_link_libraries(IO Object)
	target_link_libraries(IO SDL2)
endif()
