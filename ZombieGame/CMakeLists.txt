## TODO: Add game lib -- extract code from main.cpp into lib

## setting game sources:
set(GAME_SOURCE_FILES main.cpp)
add_executable(${PROJECT_NAME} ${GAME_SOURCE_FILES})

target_link_libraries(${PROJECT_NAME}

## OTHER LIBS: ##
	${Boost_LIBRARIES}
	${SDL2_LIBRARY} 
	${OPENGL_LIBRARIES} 
	${GLM_LIBRARIES}

## SGE LIBS: ##
	Action
	IO
	Level
	Logic
	Object
	ObjectManager
	Renderer
	Scene
	Utils
	PicoPNG)
