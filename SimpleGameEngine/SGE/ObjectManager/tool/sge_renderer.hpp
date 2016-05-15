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
		this->current = this->oManager->currentScene;

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
		assert(this->current);

		static glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
		static SGE::Color color(255, 255, 255, 255);
		
		std::vector<BackgroundElement>& background = this->current->getLevel().getBackground();
        std::vector<WorldElement>& world = this->current->getLevel().getWorld();

		/*for (int y = 0; y < Y; ++y) {
			for (int x = 0; x < X; ++x) {
				glm::vec4 destRect(x * TILE_WIDTH, y * TILE_WIDTH, TILE_WIDTH, TILE_WIDTH);
				BackgroundElement& e = background[112 * y + x];
				if(e.getPath().compare(".")==0) continue;
                GLTexture texture = this->rManager->getTexture(e.getPath().c_str());
				this->sceneBatch->draw(destRect, uv, texture.id, 0.0f, color);
			}
		}*/
		Rectangle* tile = reinterpret_cast<Rectangle*>(getBaseTileShape());
		const float width = tile->getWidth();
		const float height = tile->getHeight();

		std::for_each(background.begin(),background.end(),[=](BackgroundElement& e){
			glm::vec4 destRect(e.getX() - width*.5f , e.getY()-height*.5f, width, height);
			//if (e.getPath().compare(".") == 0) return;
			//GLTexture texture = this->rManager->getTexture(e.getPath().c_str());
			this->sceneBatch->draw(destRect, uv, e.texture.id, 0.0f, color);
		});
        
        std::for_each(world.begin(),world.end(),[=](WorldElement& e){
			glm::vec4 destRect(e.getX() - width*.5f, e.getY() - height*.5f, width, height);
            //if (e.getPath().compare(".") == 0) return;
            e.texture = this->oManager->rManager->getTexture(e.getPath().c_str());
            this->sceneBatch->draw(destRect, uv, e.texture.id, 0.0f, color);
        });
	}

	void ObjectManager::Renderer::renderObjects() {
        this->camera_handler->updateCamera();
        
        static glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
        static SGE::Color color(255, 255, 255, 255);
        
        std::vector<ObjectID>& objects = this->current->getObjects();
        Rectangle* rect = nullptr;
        Circle* circle = nullptr;
        
//        glm::vec4 destRect(id.obj->getX() - rect->getWidth()*.5f, id.obj->getY() - rect->getHeight()*.5f, rect->getWidth(), rect->getHeight());
        glm::vec4 destRect(.0f,.0f,.0f,.0f);
        
        for(auto id : objects)
        {
            switch (id.obj->getShape()->getType()) {
                case ShapeType::Circle:
                {
                    circle=reinterpret_cast<Circle*>(id.obj->getShape());
                    const float radius = circle->getRadius();
                    destRect = {id.obj->getX() - radius, id.obj->getY() - radius, radius*2.f, radius*2.f};
                    this->objectBatch->draw(destRect, uv, id.obj->texture.id, .0f, color);
                }break;
                    
                case ShapeType::Rectangle:
                {
                    rect=reinterpret_cast<Rectangle*>(id.obj->getShape());
                    destRect = {id.obj->getX() - rect->getWidth()*.5f, id.obj->getY() - rect->getHeight()*.5f, rect->getWidth(), rect->getHeight()};
                    this->objectBatch->draw(destRect, uv, id.obj->texture.id, .0f, color);
                }break;
                    
                default:
                    break;
            }
        }
	}
}

#endif // !SGE_RENDERER_HPP
