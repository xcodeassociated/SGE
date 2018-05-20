set (LogicSOURCES
		sge_logic.hpp
		sge_logic.cpp)

set (LogicsCameraSOURCES
		Logics/Camera/sge_logic_camera_zoom.hpp
		Logics/Camera/sge_logic_camera_zoom.cpp)

set (LogicsCollidersSOURCES
		Logics/Colliders/sge_logic_collide.hpp
		Logics/Colliders/sge_logic_collide.cpp
		Logics/Colliders/sge_logic_collide_basic.hpp
		Logics/Colliders/sge_logic_collide_basic.cpp
		Logics/Colliders/sge_logic_collide_group.hpp
		Logics/Colliders/sge_logic_collide_group.cpp
		Logics/Colliders/sge_logic_collide_level.hpp
		Logics/Colliders/sge_logic_collide_level.cpp
		Logics/Colliders/sge_logic_collide_level_precise.hpp
		Logics/Colliders/sge_logic_collide_level_precise.cpp)

set (LogicMoversSOURCES
		Logics/Movers/sge_logic_move.hpp
		Logics/Movers/sge_logic_move.cpp)
		
set (LogicWorldSOURCES
		Logics/World/sge_worldstep.hpp
		Logics/World/sge_worldstep.cpp)

add_library (Logic
		${LogicSOURCES}
		${LogicsCameraSOURCES}
		${LogicsCollidersSOURCES}
		${LogicMoversSOURCES}
		${LogicWorldSOURCES})

target_link_libraries(Logic
		Object
		IO
		ActionHandler
		Utils)
		
if(WIN32)
	include(GenerateExportHeader)
	generate_export_header(Logic EXPORT_FILE_NAME ${CMAKE_BINARY_DIR}/exports/logic_export.h)
endif()

install(TARGETS Logic DESTINATION "${CMAKE_INSTALL_PREFIX}/lib")