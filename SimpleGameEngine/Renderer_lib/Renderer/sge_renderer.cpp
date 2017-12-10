#include "sge_renderer.hpp"
#include "sge_shape_rectangle.hpp"
#include "sge_shape_circle.hpp"
#include "sge_game.hpp"
#include "sge_window_manager.hpp"
#include "sge_camera2d.hpp"
#include "sge_camera_handler.hpp"
#include "sge_sprite_batch.hpp"
#include "sge_shader.hpp"
#include "sge_scene.hpp"
#include <sge_macro.hpp>

#include <glm/glm.hpp>
#include <SDL.h>

namespace SGE
{
	Renderer::Renderer(std::pair<int, int> res, Game* game, WindowManager* w, CameraHandler* c) noexcept :
	width(res.first),
		height(res.second),
		game(game),
		window_manager(w),
		camera_handler(c)
	{
		;
	}

	void Renderer::initShader()
	{
		this->shaderProgram = new Shader();

		this->shaderProgram->doShaders(VERT, FRAG);

		this->shaderProgram->addAttribute("vertexPosition");
		this->shaderProgram->addAttribute("vertexColor");
		this->shaderProgram->addAttribute("vertexUV");

		this->shaderProgram->linkShaders();
	}

	void Renderer::spriteBatchInit()
	{
		this->sceneBatch = new SpriteBatch;
		this->objectBatch = new SpriteBatch;

		this->sceneBatch->init();
		this->objectBatch->init();
	}

	void Renderer::render()
	{
		this->current = this->game->currentScene;

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

	void Renderer::renderLevel()
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
			glm::vec4 destRect(e.getX() - width*.5f, e.getY() - height*.5f, width, height);
			this->sceneBatch->draw(destRect, uv, e.texture.id, 0.0f, color);
		});

		std::for_each(world.begin(), world.end(), [=](WorldElement& e) {
			glm::vec4 destRect(e.getX() - width*.5f, e.getY() - height*.5f, width, height);
			e.texture = this->game->rManager->getTexture(e.getPath().c_str());
			this->sceneBatch->draw(destRect, uv, e.texture.id, 0.0f, color);
		});
	}

	void Renderer::renderObjects()
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
			switch (id->getShape()->getType()) {
			case ShapeType::Circle:
			{
				circle = reinterpret_cast<Circle*>(id->getShape());
				const float radius = circle->getRadius();
				destRect = { id->getX() - radius, id->getY() - radius, radius*2.f, radius*2.f };
				this->objectBatch->draw(destRect, uv, id->texture.id, .0f, color);
			}break;

			case ShapeType::Rectangle:
			{
				rect = reinterpret_cast<Rectangle*>(id->getShape());
				destRect = { id->getX() - rect->getWidth()*.5f, id->getY() - rect->getHeight()*.5f, rect->getWidth(), rect->getHeight() };
				this->objectBatch->draw(destRect, uv, id->texture.id, .0f, color);
			}break;

			default:
				break;
			}
		}
	}
}
