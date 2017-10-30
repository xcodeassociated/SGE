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
        int width = 0, height = 0;
        ObjectManager* oManager = nullptr;
        SpriteBatch* sceneBatch = nullptr;
        SpriteBatch* objectBatch = nullptr;
        CameraHandler* camera_handler = nullptr;
        Shader* shaderProgram = nullptr;
        WindowManager* window_manager = nullptr;
        Scene* current = nullptr;

        void renderLevel(void);

        void renderObjects(void);

    public:
        Renderer(std::pair<int, int>, ObjectManager *, WindowManager *, CameraHandler *) noexcept;

        void initShader(void);

        void spriteBatchInit(void);

        void render(void);

    };

}

#endif // !SGE_RENDERER_HPP
