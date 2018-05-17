set (LevelSOURCES
	sge_level.hpp
	sge_level.cpp)

set (LevelParserSOURCES 
	LevelParser/sge_level_parser.hpp
	LevelParser/sge_level_parser.cpp)

add_library (Level
		${LevelSOURCES}
		${LevelParserSOURCES})

target_link_libraries(Level
		Object
		Utils)

install(TARGETS Level DESTINATION "${CMAKE_INSTALL_PREFIX}/lib")