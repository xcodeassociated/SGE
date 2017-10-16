set (TimingSOURCES
	Timing/sge_fps_limiter.hpp
	Timing/sge_fps_limiter.cpp)

set (UtilsSOURCES
	Utils/sge_utils.hpp
	Utils/sge_utils.cpp)

add_library (Utils SHARED 
		${TimingSOURCES}
		${UtilsSOURCES})
if(WIN32)
	##Add dependencies
	target_link_libraries(Utils SDL2)
endif()
