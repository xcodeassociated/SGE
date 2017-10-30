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
	Sprite/sge_vertex.cpp)

set (SpriteBatchSOURCES
		SpriteBatch/sge_sprite_batch.hpp
		SpriteBatch/sge_sprite_batch.cpp)

set (TextureCacheSOURCES
	TextureCache/sge_texture_cache.hpp
	TextureCache/sge_texture_cache.cpp)

set (TextureLoaderSOURCES
	TextureLoader/sge_imageLoader.hpp
	TextureLoader/sge_imageLoader.cpp)

add_library (Renderer SHARED 
		${ResourceManagerSOURCES}
		${ShadersSOURCES}
		${SpriteSOURCES}
		${SpriteBatchSOURCES}
		${TextureCacheSOURCES}
		${TextureLoaderSOURCES})
		
target_link_libraries(Renderer 
	${OPENGL_LIBRARIES}
	${GLEW_LIBRARIES} 
	PicoPNG
	IO)
