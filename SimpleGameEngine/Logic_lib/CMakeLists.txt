set (LogicSOURCES
		Logic/sge_logic.hpp
		Logic/sge_logic.cpp)

set (LogicsCameraSOURCES
		Logic/Logics/Camera/sge_logic_camera_zoom.hpp
		Logic/Logics/Camera/sge_logic_camera_zoom.cpp)

set (LogicsCollidersSOURCES
		Logic/Logics/Colliders/sge_logic_collide.hpp
		Logic/Logics/Colliders/sge_logic_collide.cpp
		Logic/Logics/Colliders/sge_logic_collide_basic.hpp
		Logic/Logics/Colliders/sge_logic_collide_basic.cpp
		Logic/Logics/Colliders/sge_logic_collide_group.hpp
		Logic/Logics/Colliders/sge_logic_collide_group.cpp
		Logic/Logics/Colliders/sge_logic_collide_level.hpp
		Logic/Logics/Colliders/sge_logic_collide_level.cpp
		Logic/Logics/Colliders/sge_logic_collide_level_precise.hpp
		Logic/Logics/Colliders/sge_logic_collide_level_precise.cpp)

set (LogicMoversSOURCES
		Logic/Logics/Movers/sge_logic_move.hpp
		Logic/Logics/Movers/sge_logic_move.cpp)

add_library (Logic SHARED
		${LogicSOURCES}
		${LogicsCameraSOURCES}
		${LogicsCollidersSOURCES}
		${LogicMoversSOURCES})

target_link_libraries(Logic
		Object
		IO
		Action
		Utils)
		
if(WIN32)
	include(GenerateExportHeader)
	generate_export_header(Logic)
endif()
