#ifndef SGE_RENDERER_HPP
#define SGE_RENDERER_HPP

/**
 * TODO: THIS HAS TO BE MOVED TO RENDERER LIB!!!
 */

#include <algorithm>

namespace SGE {

    class CameraHandler;
    class WindowManager;
    class ObjectManager;
    class SpriteBatch;
    class Shader;
    class Scene;

    class Renderer {
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
	    ObjectManager* oManager = nullptr;
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
        void renderLevel(void);

	    /**
         * \brief 
         */
        void renderObjects(void);

    public:
	    /**
         * \brief 
         */
        Renderer(std::pair<int, int>, ObjectManager *, WindowManager *, CameraHandler *) noexcept;

	    /**
         * \brief 
         */
        void initShader(void);

	    /**
         * \brief 
         */
        void spriteBatchInit(void);

	    /**
         * \brief 
         */
        void render(void);

    };

}

#endif // !SGE_RENDERER_HPP
