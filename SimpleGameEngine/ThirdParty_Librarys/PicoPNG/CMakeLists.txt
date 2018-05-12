set(PicoPNGSOURCES
	picopng.cpp
	picopng.h)

add_library(PicoPNG ${PicoPNGSOURCES})

install(TARGETS PicoPNG DESTINATION "${CMAKE_INSTALL_PREFIX}/lib")
