set(ShapeSOURCES
        sge_shape.hpp
        sge_shape.cpp
        sge_shape_circle.cpp
        sge_shape_circle.hpp
        sge_shape_rectangle.cpp
        sge_shape_rectangle.hpp
        sge_shape_type.hpp
        sge_shapeless.cpp
        sge_shapeless.hpp)

add_library(Shape ${ShapeSOURCES})

install(TARGETS Shape DESTINATION "${CMAKE_INSTALL_PREFIX}/lib")