#include "sge_renderer.hpp"
#include "../Shape/sge_shape_rectangle.hpp"
#include "../Shape/sge_shape_circle.hpp"
#include "../Camera2d/sge_camera2d.hpp"
#include "../Sprite/sge_sprite.hpp"
#include "Window/sge_window.hpp"
#include "SpriteBatch/sge_sprite_batch.hpp"
#include "Shaders/sge_shader.hpp"

#include <utility>
#include <string>
#include <vector>
#include <stdexcept>

#include <glm/glm.hpp>
#include <SDL.h>

SGE::Renderer::Renderer(const std::string& _vert, const std::string& _frag, std::pair<int, int> res,
    std::vector<std::string> shadersAttributes)
  : vert(_vert),
    frag(_frag),
    width(res.first),
    height(res.second)
{
//    try
//    {
        this->initShader(std::forward<std::vector<std::string>>(shadersAttributes));
        this->spriteBatchInit();
//    }
//    catch (...) 
//    {}
}

void SGE::Renderer::initShader(std::vector<std::string> && shadersAttributes)
{
    this->shaderProgram = new Shader();

    if (this->vert.empty() || this->frag.empty())
        throw std::runtime_error{"vert or frag missing"};

    this->shaderProgram->doShaders(this->vert.c_str(), this->frag.c_str());

    for (const auto& attrib : shadersAttributes)
    {
        assert(!attrib.empty());
        this->shaderProgram->addAttribute(attrib.c_str());
    }

    this->shaderProgram->linkShaders();
}

void SGE::Renderer::spriteBatchInit()
{
    this->objectBatch = new SpriteBatch;
    this->objectBatch->init();
}

void SGE::Renderer::setContext(Camera2d* camera, float clearDepth, GLbitfield mask)
{
    glClearDepth(clearDepth);
    glClear(mask);

    this->shaderProgram->use();

    glActiveTexture(GL_TEXTURE0);
    GLint textureLocation = this->shaderProgram->getUniformLocation("mySampler");
    glUniform1i(textureLocation, 0);

    GLint pLocation = this->shaderProgram->getUniformLocation("P");
    glm::mat4 cameraMatrix = camera->getCameraMatrix();
    glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

    this->objectBatch->begin();   
    // render sprites here ...
}

void SGE::Renderer::usetContext(GLuint texture, SDL_Window* window)
{
    this->objectBatch->end();
    this->objectBatch->renderBatch();

    glBindTexture(GL_TEXTURE_2D, texture);
    this->shaderProgram->unuse();
	SDL_GL_SwapWindow(window);
}

void SGE::Renderer::render(Sprite* sprite, const glm::vec4& uv, Color color, glm::vec4 destRect)
{
        assert(sprite);

		if (!(sprite->getVisible()))
			return;

        switch (sprite->getShape()->getType())
		{
			case ShapeType::Circle:
			{
				Circle* circle = reinterpret_cast<Circle*>(sprite->getShape());
				const float radius = circle->getRadius();
			
            	destRect = { sprite->getX() - radius, sprite->getY() - radius, 
                    radius * 2.f, radius * 2.f };

				this->objectBatch->draw(destRect, uv, sprite->getTexture()->texture.id, .0f, color);

				break;
			}
			case ShapeType::Rectangle:
			{
				Rectangle* rect = reinterpret_cast<Rectangle*>(sprite->getShape());

				destRect = { sprite->getX() - rect->getWidth()*.5f, 
                    sprite->getY() - rect->getHeight() * .5f, rect->getWidth(), rect->getHeight() };

				this->objectBatch->draw(destRect, uv, sprite->getTexture()->texture.id, .0f, color);

				break;
			}
			default:
				break;
        }
}
