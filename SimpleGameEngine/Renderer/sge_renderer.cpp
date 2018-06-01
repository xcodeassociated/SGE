#include "sge_renderer.hpp"
#include "../Object/Shape/sge_shape_rectangle.hpp"
#include "../Object/Shape/sge_shape_circle.hpp"
#include "WindowManager/sge_window_manager.hpp"
#include "../Object/Camera2d/sge_camera2d.hpp"
#include "CameraHandler/sge_camera_handler.hpp"
#include "SpriteBatch/sge_sprite_batch.hpp"
#include "Shaders/sge_shader.hpp"
#include "../Scene/sge_scene.hpp"
#include "ResourceManager/sge_resource_manager.hpp"

#include <glm/glm.hpp>
#include <SDL.h>

SGE::Renderer::Renderer(const std::string& _vert, const std::string& _frag, std::pair<int, int> res, WindowManager* w, CameraHandler* c, ResourceManager* resourceManager) noexcept :
    vert(_vert),
    frag(_frag),
    width(res.first),
    height(res.second),
    resourceManager(resourceManager),
    window_manager(w),
    camera_handler(c)
{}

void SGE::Renderer::initShader()
{
    this->shaderProgram = new Shader();

    if (this->vert.empty() || this->frag.empty())
        throw std::runtime_error{"vert or frag missing"};

    this->shaderProgram->doShaders(this->vert.c_str(), this->frag.c_str());

    this->shaderProgram->addAttribute("vertexPosition");
    this->shaderProgram->addAttribute("vertexColor");
    this->shaderProgram->addAttribute("vertexUV");

    this->shaderProgram->linkShaders();
}

void SGE::Renderer::spriteBatchInit()
{
    this->sceneBatch = new SpriteBatch;
    this->objectBatch = new SpriteBatch;

    this->sceneBatch->init();
    this->objectBatch->init();
}

void SGE::Renderer::render(SGE::Scene* scene)
{
    this->current = scene;

    glClearDepth(1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    this->shaderProgram->use();

    glActiveTexture(GL_TEXTURE0);
    GLint textureLocation = this->shaderProgram->getUniformLocation("mySampler");
    glUniform1i(textureLocation, 0);

    GLint pLocation = this->shaderProgram->getUniformLocation("P");
    glm::mat4 cameraMatrix = this->camera_handler->getCameraMatrix();
    glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

    this->sceneBatch->begin();
    {
        this->renderLevel();
    }
    this->sceneBatch->end();
    this->sceneBatch->renderBatch();

    this->objectBatch->begin();
    {
        this->renderObjects();
    }
    this->objectBatch->end();
    this->objectBatch->renderBatch();

    glBindTexture(GL_TEXTURE_2D, 0);
    this->shaderProgram->unuse();

    SDL_GL_SwapWindow(this->window_manager->getWindow());
}

void SGE::Renderer::renderLevel()
{
    assert(this->current);

    static glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
    static SGE::Color color(255, 255, 255, 255);

    std::vector<BackgroundElement>& background = this->current->getLevel().getBackground();
    std::vector<WorldElement>& world = this->current->getLevel().getWorld();

    Rectangle* tile = reinterpret_cast<Rectangle*>(getBaseTileShape());
    const float width = tile->getWidth();
    const float height = tile->getHeight();

    std::for_each(background.begin(), background.end(), [=](BackgroundElement& e) {
		if (!(e.getVisible() && e.getDrawable()))
			return;
        glm::vec4 destRect(e.getX() - width*.5f, e.getY() - height*.5f, width, height);
        this->sceneBatch->draw(destRect, uv, e.texture.id, 0.0f, color);
    });

    std::for_each(world.begin(), world.end(), [=](WorldElement& e) {
		if (!(e.getVisible() && e.getDrawable()))
			return;
        glm::vec4 destRect(e.getX() - width*.5f, e.getY() - height*.5f, width, height);
        e.texture = this->resourceManager->getTexture(e.getPath().c_str());
        this->sceneBatch->draw(destRect, uv, e.texture.id, 0.0f, color);
    });
}

void SGE::Renderer::renderObjects()
{
    this->camera_handler->updateCamera();

    static glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
    static SGE::Color color(255, 255, 255, 255);

    std::vector<Object*>& objects = this->current->getObjects();
    Rectangle* rect = nullptr;
    Circle* circle = nullptr;

    glm::vec4 destRect(.0f, .0f, .0f, .0f);

    for (auto id : objects)
    {
		if (!(id->getVisible() && id->getDrawable()))
			continue;
        switch (id->getShape()->getType())
		{
			case ShapeType::Circle:
			{
				circle = reinterpret_cast<Circle*>(id->getShape());
				const float radius = circle->getRadius();
				destRect = { id->getX() - radius, id->getY() - radius, radius*2.f, radius*2.f };
				this->objectBatch->draw(destRect, uv, id->texture.id, .0f, color);
				break;
			}
			case ShapeType::Rectangle:
			{
				rect = reinterpret_cast<Rectangle*>(id->getShape());
				destRect = { id->getX() - rect->getWidth()*.5f, id->getY() - rect->getHeight()*.5f, rect->getWidth(), rect->getHeight() };
				this->objectBatch->draw(destRect, uv, id->texture.id, .0f, color);
				break;
			}
			default:
				break;
        }
    }
}

