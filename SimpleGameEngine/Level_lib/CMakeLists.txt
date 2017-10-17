set (LevelSOURCES
	Level/sge_level.hpp
	Level/sge_level.cpp)

set (LevelParserSOURCES 
	LevelParser/sge_level_parser.hpp
	LevelParser/sge_level_parser.cpp)

add_library (Level SHARED
		${LevelSOURCES}
		${LevelParserSOURCES})
if(WIN32)
	target_link_libraries(Level Object)
endif()
