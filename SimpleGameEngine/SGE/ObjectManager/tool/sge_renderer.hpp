#ifndef SGE_RENDERER_HPP
#define SGE_RENDERER_HPP

#include <algorithm>

namespace SGE
{
    class WindowManager;
    
	ObjectManager::Renderer::Renderer(std::pair<int, int> res, ObjectManager* m, WindowManager* w, CameraHandler* c) noexcept :
        width(res.first),
        height(res.second),
        oManager(m),
        window_manager(w),
        camera_handler(c)
	{
        ;
	}

	void ObjectManager::Renderer::setLevel(Level* l)
	{
		this->level = l;
	}

	void ObjectManager::Renderer::initResourceManager() {
		this->rManager = ResourceManager::getSingleton();
	}

	void ObjectManager::Renderer::initShader() {
		this->shaderProgram = new Shader();

		this->shaderProgram->doShaders(VERT, FRAG);

		this->shaderProgram->addAttribute("vertexPosition");
		this->shaderProgram->addAttribute("vertexColor");
		this->shaderProgram->addAttribute("vertexUV");

		this->shaderProgram->linkShaders();
	}

//	void ObjectManager::Renderer::initCamera() {
//		this->camera = new Camera2d(width, height);
//        
//        this->camera->setScale(0.05f);
//        this->camera->setPosition(glm::vec2(0, 0));
//	}

	void ObjectManager::Renderer::spriteBatchInit() {
		this->sceneBatch = new SpriteBatch;
		this->objectBatch = new SpriteBatch;

		this->sceneBatch->init();
		this->objectBatch->init();
	}

	void ObjectManager::Renderer::render() {
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
        
		SDL_GL_SwapWindow( this->window_manager->getWindow() );
	}

	void ObjectManager::Renderer::renderLevel() {
		assert(this->level);

		static glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
		static SGE::Color color(255, 255, 255, 255);
		static const int TILE_WIDTH = 64;
		
		const size_t X = this->level->getWidth();
		const size_t Y = this->level->getHeight();
		std::vector<BackgroundElement>& background = this->level->getBackground();
        std::vector<WorldElement>& world = this->level->getWorld();

		/*for (int y = 0; y < Y; ++y) {
			for (int x = 0; x < X; ++x) {
				glm::vec4 destRect(x * TILE_WIDTH, y * TILE_WIDTH, TILE_WIDTH, TILE_WIDTH);
				BackgroundElement& e = background[112 * y + x];
				if(e.getPath().compare(".")==0) continue;
                GLTexture texture = this->rManager->getTexture(e.getPath().c_str());
				this->sceneBatch->draw(destRect, uv, texture.id, 0.0f, color);
			}
		}*/
        
		std::for_each(background.begin(),background.end(),[=](BackgroundElement& e){
				glm::vec4 destRect(e.getX() * TILE_WIDTH, e.getY() * TILE_WIDTH, TILE_WIDTH, TILE_WIDTH);
				if (e.getPath().compare(".") == 0) return;
				GLTexture texture = this->rManager->getTexture(e.getPath().c_str());
				this->sceneBatch->draw(destRect, uv, texture.id, 0.0f, color);
			});
        
        std::for_each(world.begin(),world.end(),[=](WorldElement& e){
            glm::vec4 destRect(e.getX() * TILE_WIDTH, e.getY() * TILE_WIDTH, TILE_WIDTH, TILE_WIDTH);
            if (e.getPath().compare(".") == 0) return;
            GLTexture texture = this->rManager->getTexture(e.getPath().c_str());
            this->sceneBatch->draw(destRect, uv, texture.id, 0.0f, color);
        });
	}

	void ObjectManager::Renderer::renderObjects() {
        this->camera_handler->updateCamera();
	}
}

#endif // !SGE_RENDERER_HPP
