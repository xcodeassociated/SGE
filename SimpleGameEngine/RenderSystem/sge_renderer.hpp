#ifndef SGE_RENDERER_HPP
#define SGE_RENDERER_HPP

#include "Color/sge_color.hpp"
#include "UV/sge_uv.hpp"

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <algorithm>
#include <string>
#include <vector>

#include <SDL.h>

namespace SGE
{
    class Window;
    class SpriteBatch;
    class Shader;
    class Camera2d;
    class Sprite;

    class Renderer
    {
	    int width = 0;
	    int height = 0;
        SpriteBatch* objectBatch = nullptr;
        Shader* shaderProgram = nullptr;
        std::string vert = "";
        std::string frag = "";

    protected:
        void initShader(std::vector<std::string> && shadersAttributes);
        void spriteBatchInit();

    public:
        Renderer(const std::string& vert, const std::string& frag, std::pair<int, int> res,
            std::vector<std::string> shadersAttributes = {"vertexPosition", "vertexColor", "vertexUV"});

        void setContext(Camera2d* camera, float clearDepth = 1.0f, 
            GLbitfield mask = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        void usetContext(GLuint texture, SDL_Window* window);

        void render(Sprite* sprite, const glm::vec4& uv, Color color, glm::vec4 destRect);
    };

}

#endif // !SGE_RENDERER_HPP
