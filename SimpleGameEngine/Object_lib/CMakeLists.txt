set (ObjectCameraSOURCES
	Camera2d/sge_camera2d.hpp
	Camera2d/sge_camera2d.cpp)

set (ObjectIDSOURCES
	ID/sge_id.hpp
	ID/sge_id.cpp)

set (ObjectSOURCES
	Object/sge_object.hpp
	Object/sge_object.cpp
	Object/sge_logic_priority.hpp
	Object/sge_object_bind.hpp
	Object/sge_object_bind.cpp
	Object/sge_object_id.hpp
	Object/sge_object_id.cpp)

set (ObjectBackgroundElementSOURCES
	Object/BackgroundElement/sge_background_element.hpp
	Object/BackgroundElement/sge_background_element.cpp
	Object/BackgroundElement/sge_world_element.hpp
	Object/BackgroundElement/sge_world_element.cpp)

set (ObjectInterfaceSOURCES
	Object/Interface/sge_button.hpp
	Object/Interface/sge_button.cpp
	Object/Interface/sge_interface.hpp
	Object/Interface/sge_interface.cpp
	Object/Interface/sge_label.hpp
	Object/Interface/sge_label.cpp)

set (ObjectReactiveSOURCES
	Object/Reactive/sge_being.hpp
	Object/Reactive/sge_being.cpp
	Object/Reactive/sge_player.hpp
	Object/Reactive/sge_player.cpp
	Object/Reactive/sge_reactive.hpp
	Object/Reactive/sge_reactive.cpp)

set (ObjectShapeSOURCES
	Object/Shape/sge_shape.hpp
	Object/Shape/sge_shape.cpp
	Object/Shape/sge_shape_type.hpp
	Object/Shape/sge_shape_circle.hpp
	Object/Shape/sge_shape_circle.cpp
	Object/Shape/sge_shape_rectangle.hpp
	Object/Shape/sge_shape_rectangle.cpp
	Object/Shape/sge_shapeless.hpp
	Object/Shape/sge_shapeless.cpp)

add_library (Object SHARED 
		${ObjectCameraSOURCES}
		${ObjectIDSOURCES}
		${ObjectSOURCES}
		${ObjectBackgroundElementSOURCES}
		${ObjectInterfaceSOURCES}
		${ObjectReactiveSOURCES}
		${ObjectShapeSOURCES})
