set (LoggerSOURCES
		Logger/sge_logger.hpp
		Logger/sge_logger.cpp)

set (TimingSOURCES
		Timing/sge_fps_limiter.hpp
		Timing/sge_fps_limiter.cpp)

set (UtilsSOURCES
		Utils/sge_utils.hpp
		Utils/sge_utils.cpp)

add_library (Utils SHARED
		${LoggerSOURCES}
		${TimingSOURCES}
		${UtilsSOURCES})
		
target_link_libraries(Utils
		${Boost_LIBRARIES}
		${SDL2_LIBRARY})