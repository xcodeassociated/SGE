set (IOSOURCES_InputManager
		InputManager/sge_input_manager.hpp
		InputManager/sge_input_manager.cpp)

set (IOSOURCES_KeyboardState
		Key/sge_key.hpp
		KeyboardState/sge_keyboard_state.hpp
		KeyboardState/sge_keyboard_state.cpp)

set (IOSOURCES_Mouse
		Mouse/sge_mouse.hpp
		Mouse/sge_mouse.cpp)

add_library(IO
		${IOSOURCES_InputManager}
		${IOSOURCES_KeyboardState}
		${IOSOURCES_Mouse})
		
target_link_libraries(IO
		Utils
		${SDL2_LIBRARY})

install(TARGETS IO DESTINATION "${CMAKE_INSTALL_PREFIX}/lib")