set (RendererSOURCES
		sge_renderer.hpp
		sge_renderer.cpp)

set (CameraHandlerSOURCES
		CameraHandler/sge_camera_handler.hpp
		CameraHandler/sge_camera_handler.cpp)

set (WindowManagerSOURCES
		WindowManager/sge_window_manager.hpp
		WindowManager/sge_window_manager.cpp)

set (ResourceManagerSOURCES
		ResourceManager/sge_resource_manager.hpp
		ResourceManager/sge_resource_manager.cpp)

set (ShadersSOURCES
		Shaders/sge_shader.hpp
		Shaders/sge_shader.cpp)

set (VertexSOURCES
		Vertex/sge_vertex.hpp
		Vertex/sge_vertex.cpp)

set (SpriteBatchSOURCES
		SpriteBatch/sge_sprite_batch.hpp
		SpriteBatch/sge_sprite_batch.cpp
		SpriteBatch/sge_glyph.hpp
		SpriteBatch/sge_glyph_type.hpp
		SpriteBatch/sge_render_batch.hpp)

set (TextureCacheSOURCES
		TextureCache/sge_texture_cache.hpp
		TextureCache/sge_texture_cache.cpp)

set (TextureLoaderSOURCES
		TextureLoader/sge_imageLoader.hpp
		TextureLoader/sge_imageLoader.cpp)

set (IOManagerSOURCES
		IOManager/sge_io_manager.hpp
		IOManager/sge_io_manager.cpp)

add_library (Renderer
		${RendererSOURCES}
		${ResourceManagerSOURCES}
		${ShadersSOURCES}
		${VertexSOURCES}
		${SpriteBatchSOURCES}
		${TextureCacheSOURCES}
		${TextureLoaderSOURCES}
		${CameraHandlerSOURCES}
		${WindowManagerSOURCES}
		${IOManagerSOURCES})
		
target_link_libraries(Renderer
		Sprite
		Shape
		Utils
		Camera2d
		PicoPNG
		Utils
		${OPENGL_LIBRARIES}
		${GLEW_LIBRARIES})

install(TARGETS Renderer DESTINATION "${CMAKE_INSTALL_PREFIX}/lib")
