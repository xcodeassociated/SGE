set (LoggerSOURCES
		Logger/sge_logger.hpp
		Logger/sge_logger.cpp)

set (TimingSOURCES
		Timing/sge_fps_limiter.hpp
		Timing/sge_fps_limiter.cpp)

set (UtilsSOURCES
		sge_utils.hpp
		sge_utils.cpp)

add_library (Utils
		${LoggerSOURCES}
		${TimingSOURCES}
		${UtilsSOURCES})
		
target_link_libraries(Utils
		${Boost_LIBRARIES}
		${SDL2_LIBRARY})
		
if(WIN32)
	include(GenerateExportHeader)
	generate_export_header(Utils EXPORT_FILE_NAME ${CMAKE_BINARY_DIR}/exports/utils_export.h)
endif()

install(TARGETS Utils DESTINATION "${CMAKE_INSTALL_PREFIX}/lib")