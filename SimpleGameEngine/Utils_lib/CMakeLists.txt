set (TimingSOURCES
	Timing/sge_fps_limiter.hpp
	Timing/sge_fps_limiter.cpp)

set (UtilsSOURCES
	Utils/sge_utils.hpp
	Utils/sge_utils.cpp)

add_library (Utils SHARED 
		${TimingSOURCES}
		${UtilsSOURCES})
		
target_link_libraries(Utils ${SDL2_LIBRARY})