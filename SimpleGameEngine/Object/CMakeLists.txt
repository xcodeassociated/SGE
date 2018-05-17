set (ObjectCameraSOURCES
		Camera2d/sge_camera2d.hpp
		Camera2d/sge_camera2d.cpp)

set (ObjectSOURCES
		sge_object.hpp
		sge_object.cpp
		sge_logic_priority.hpp)

set (ObjectBackgroundElementSOURCES
		BackgroundElement/sge_background_element.hpp
		BackgroundElement/sge_background_element.cpp)

set (ObjectWorldElementSOURCES
		WorldElement/sge_world_element.hpp
		WorldElement/sge_world_element.cpp)

set (ObjectReactiveSOURCES
		Reactive/sge_being.hpp
		Reactive/sge_being.cpp
		Reactive/sge_player.hpp
		Reactive/sge_player.cpp
		Reactive/sge_reactive.hpp
		Reactive/sge_reactive.cpp)

set (ObjectShapeSOURCES
		Shape/sge_shape.hpp
		Shape/sge_shape.cpp
		Shape/sge_shape_type.hpp
		Shape/sge_shape_circle.hpp
		Shape/sge_shape_circle.cpp
		Shape/sge_shape_rectangle.hpp
		Shape/sge_shape_rectangle.cpp
		Shape/sge_shapeless.hpp
		Shape/sge_shapeless.cpp)

add_library (Object
		${ObjectCameraSOURCES}
		${ObjectSOURCES}
		${ObjectBackgroundElementSOURCES}
		${ObjectWorldElementSOURCES}
		${ObjectReactiveSOURCES}
		${ObjectShapeSOURCES})

target_link_libraries(Object
			Utils
			Box2D)

install(TARGETS Object DESTINATION "${CMAKE_INSTALL_PREFIX}/lib")