#ifndef SGE_RENDERER_HPP
#define SGE_RENDERER_HPP

namespace SGE
{
	ObjectManager::Renderer::Renderer(std::pair<int, int> res, ObjectManager* m) : width(res.first), height(res.second), oManager(m)
	{

	}

	void ObjectManager::Renderer::setBackground(std::vector<BackgroundElement>* b)
	{
		this->background = b;
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

	void ObjectManager::Renderer::initCamera() {
		this->camera = new Camera2d(width, height);

		GLint pLocation = this->shaderProgram->getUniformLocation("P");
		glm::mat4 cameraMatrix = this->camera->getCameraMatrix();
		glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));
	}

	void ObjectManager::Renderer::spriteBatchInit() {
		this->sceneBatch = new SpriteBatch;
		this->objecBatch = new SpriteBatch;

		this->sceneBatch->init();
		this->objecBatch->init();
	}

	void ObjectManager::Renderer::createWindow()
	{
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
			throw "error:    SDL_init";
	}

	void ObjectManager::Renderer::showWindow() {
		this->window = SDL_CreateWindow("SGE", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, this->width, this->height, SDL_WINDOW_OPENGL);

		if (this->window == nullptr)
			throw "error: ";

		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

		SDL_GLContext glContext = SDL_GL_CreateContext(this->window);
		if (glContext == nullptr) throw "";

		glewExperimental = GL_TRUE;
		GLenum glewCheck = glewInit();
		if (glewCheck != GLEW_OK) throw "";

		glClearColor(.7f, .7f, .7f, 1.0f);

		SDL_GL_SetSwapInterval(1);

		const GLubyte* version = glGetString(GL_VERSION);
		const char* glVersionChar = reinterpret_cast< const char* >(version);

		const GLubyte* render = glGetString(GL_RENDERER);
		const char* glRenderChar = reinterpret_cast< const char* >(render);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		GLuint VertexArrayID;
		glGenVertexArrays(1, &VertexArrayID);
		glBindVertexArray(VertexArrayID);

		SDL_ShowWindow(this->window);
	}

	void ObjectManager::Renderer::finalizeWindow() {
		SDL_DestroyWindow(this->window);
		SDL_Quit();
	}

	void ObjectManager::Renderer::render() {
		glClearDepth(1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		this->shaderProgram->use();

		glActiveTexture(GL_TEXTURE0);
		GLint textureLocation = this->shaderProgram->getUniformLocation("mySampler");
		glUniform1i(textureLocation, 0);

		this->sceneBatch->begin();
		{
			this->renderLevel();
		}
		this->sceneBatch->end();
		this->sceneBatch->renderBatch();

		this->objecBatch->begin();
		{
			this->renderObjects();
		}
		this->objecBatch->end();
		this->objecBatch->renderBatch();

		glBindTexture(GL_TEXTURE_2D, 0);
		this->shaderProgram->unuse();
		SDL_GL_SwapWindow(this->window);
	}

	void ObjectManager::Renderer::renderLevel() {
		assert(this->background && !this->background->empty());

		static glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
		static SGE::Color color(255, 255, 255, 255);
		const int TILE_WIDTH = 64;

		for (int y = 0; y < 32; y++) {
			for (int x = 0; x < 112; x++) {
				glm::vec4 destRect(x * TILE_WIDTH, y * TILE_WIDTH, TILE_WIDTH, TILE_WIDTH);

				BackgroundElement& e = this->background->at(0);
				/* static */ GLTexture texture = this->rManager->getTexture(e.getPath().c_str());
				this->sceneBatch->draw(destRect, uv, texture.id, 0.0f, color);

			}
		}

	}

	void ObjectManager::Renderer::renderObjects() {
		this->camera->update();
		//this->camera->setPosition(glm::vec2(0,0));
		this->camera->setPosition(this->camera->screenToWorld(glm::vec2(0, 0)));
	}
}

#endif // !SGE_RENDERER_HPP