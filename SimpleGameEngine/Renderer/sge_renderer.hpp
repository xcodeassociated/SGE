#ifndef SGE_RENDERER_HPP
#define SGE_RENDERER_HPP

#include <algorithm>
#include <string>

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
	    int width = 0;
	    int height = 0;

		ResourceManager* resourceManager = nullptr;
        SpriteBatch* sceneBatch = nullptr;
        SpriteBatch* objectBatch = nullptr;
        CameraHandler* camera_handler = nullptr;
        Shader* shaderProgram = nullptr;
        WindowManager* window_manager = nullptr;

        std::string vert = "";
        std::string frag = "";

        void renderLevel();

        void renderObjects();

    public:
        Renderer(const std::string& _vert, const std::string& _frag, std::pair<int, int>,
                WindowManager *, CameraHandler *, ResourceManager* resourceManager);


        void initShader();

        void spriteBatchInit();

        void render(Scene* scene);

    };

}

#endif // !SGE_RENDERER_HPP
