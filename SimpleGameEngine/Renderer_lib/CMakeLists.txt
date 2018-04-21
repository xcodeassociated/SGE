set (RendererSOURCES
		Renderer/sge_renderer.hpp
		Renderer/sge_renderer.cpp)

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

set (SpriteSOURCES
		Sprite/sge_sprite.hpp
		Sprite/sge_sprite.cpp
		Sprite/sge_vertex.hpp
		Sprite/sge_vertex.cpp
		Sprite/sge_vertex_data.hpp)

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

add_library (Renderer
		${RendererSOURCES}
		${ResourceManagerSOURCES}
		${ShadersSOURCES}
		${SpriteSOURCES}
		${SpriteBatchSOURCES}
		${TextureCacheSOURCES}
		${TextureLoaderSOURCES}
		${CameraHandlerSOURCES}
		${WindowManagerSOURCES})
		
target_link_libraries(Renderer
		Level
		Scene
		Object
		Utils
		PicoPNG
		IO
		Utils
		${OPENGL_LIBRARIES}
		${GLEW_LIBRARIES})
