#ifndef SGE_RENDERER_HPP
#define SGE_RENDERER_HPP

#include <algorithm>

namespace SGE
{
    class CameraHandler;
    class WindowManager;
    class SpriteBatch;
    class Shader;
    class Scene;
	class ResourceManager;

    class Renderer
    {
	    /**
	     * \brief 
	     */
	    int width = 0;
	    /**
	     * \brief 
	     */
	    int height = 0;
	    /**
	     * \brief 
	     */
		ResourceManager* resourceManager = nullptr;
	    /**
         * \brief 
         */
        SpriteBatch* sceneBatch = nullptr;
	    /**
         * \brief 
         */
        SpriteBatch* objectBatch = nullptr;
	    /**
         * \brief 
         */
        CameraHandler* camera_handler = nullptr;
	    /**
         * \brief 
         */
        Shader* shaderProgram = nullptr;
	    /**
         * \brief 
         */
        WindowManager* window_manager = nullptr;
	    /**
         * \brief 
         */
        Scene* current = nullptr;

	    /**
         * \brief 
         */
        void renderLevel();

	    /**
         * \brief 
         */
        void renderObjects();

    public:
	    /**
         * \brief 
         */
        Renderer(std::pair<int, int>, WindowManager *, CameraHandler *, ResourceManager* resourceManager) noexcept;

	    /**
         * \brief 
         */
        void initShader();

	    /**
         * \brief 
         */
        void spriteBatchInit();

	    /**
         * \brief 
         */
        void render(Scene* scene);

    };

}

#endif // !SGE_RENDERER_HPP
