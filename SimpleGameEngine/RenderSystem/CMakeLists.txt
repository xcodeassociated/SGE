set (RendererSOURCES
		sge_renderer.hpp
		sge_renderer.cpp)

set (WindowSOURCES
		Window/sge_window.hpp
		Window/sge_window.cpp)

set (ShadersSOURCES
		Shaders/sge_shader.hpp
		Shaders/sge_shader.cpp)

set (VertexUVSOURCES
		Vertex/sge_vertex.hpp
		Vertex/sge_vertex.cpp
		UV/sge_uv.hpp)

set (SpriteBatchSOURCES
		SpriteBatch/sge_sprite_batch.hpp
		SpriteBatch/sge_sprite_batch.cpp
		SpriteBatch/sge_glyph.hpp
		SpriteBatch/sge_glyph_type.hpp
		SpriteBatch/sge_render_batch.hpp)

set (TextureSOURCES
		Texture/sge_texture_cache.hpp
		Texture/sge_texture_cache.cpp
		Texture/sge_image_loader.hpp
		Texture/sge_image_loader.cpp)

add_library (RenderSystem
		${RendererSOURCES}
		${ShadersSOURCES}
		${VertexUVSOURCES}
		${SpriteBatchSOURCES}
		${TextureSOURCES}
		${WindowSOURCES})
		
target_link_libraries(RenderSystem
		Sprite
		Shape
		Utils
		Camera2d
		PicoPNG
		Utils
		${OPENGL_LIBRARIES}
		${GLEW_LIBRARIES})

install(TARGETS RenderSystem DESTINATION "${CMAKE_INSTALL_PREFIX}/lib")
