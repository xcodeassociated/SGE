## TODO: Add game lib -- extract code from main.cpp into lib

## setting game sources:
set(GAME_SOURCE_FILES main.cpp
		Actions.cpp 
		Actions.hpp 
		Logics.cpp 
		Logics.hpp 
		Objects.cpp
		Objects.hpp
		ZombieScene.cpp
		ZombieScene.hpp
		IntroScene.cpp
		IntroScene.hpp)

add_executable(${PROJECT_NAME} ${GAME_SOURCE_FILES})

target_link_libraries(${PROJECT_NAME}

## OTHER LIBS: ##
		${Boost_LIBRARIES}
		${SDL2_LIBRARY}
		${GLEW_LIBRARIES}
		${OPENGL_LIBRARIES}
		${GLM_LIBRARIES}

## SGE LIBS: ##
		Action
		ActionHandler
		IO
		Level
		Logic
		Object
		Game
		Renderer
		Scene
		Utils
		PicoPNG
		Box2D
)

#if(NOT WIN32)
#foreach( file_i "${Boost_LIBRARIES}")
#	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#			COMMAND ${CMAKE_COMMAND} -E copy ${file_i} ${CMAKE_BINARY_DIR}/bin)
#endforeach( file_i )
#
#foreach( file_i "${CONAN_LIB_DIRS_GLEW}")
#	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#			COMMAND ${CMAKE_COMMAND} -E copy ${file_i}/* ${CMAKE_BINARY_DIR}/bin)
#endforeach( file_i )
#endif()
##TODO: Copy SDL2 libs as well
