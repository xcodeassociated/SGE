#ifndef sge_object_manager_h
#define sge_object_manager_h

#include "../include/sge_include.hpp"
#include "../Shaders/sge_shader.hpp"
#include "../Camera2d/sge_camera2d.hpp"
#include "../SpriteBatch/SpriteBatch.hpp"
#include "../ResourceManager/sge_resource_manager.hpp"
#include "../TextureLoader/sge_glTexture.hpp"
#include "../InputManager/sge_input_manager.hpp"
#include "../Timing/sge_fps_limiter.hpp"

#include "../Relay/sge_relay_interface.hpp"

#include <initializer_list>
#include <algorithm>
#include <vector>
#include <map>
#include <stdexcept>

#include <random>
#include <ctime>

namespace SGE {
	class Object;
	class ObjectID;
	class Scene;
	class SceneID;
	class Action;
	class BackgroundElement;
	class WorldElement;

    class ObjectManager final{
		friend class Relay;

		class ActionHandler {

		};

		class Renderer {
			int width=0;
			int height=0;
			ObjectManager* oManager = nullptr;
			SpriteBatch* sceneBatch = nullptr;
			SpriteBatch* objecBatch = nullptr;
			ResourceManager* rManager = nullptr;
			Camera2d* camera = nullptr;
			SDL_Window* window = nullptr;
			Shader* shaderProgram = nullptr;
			std::vector<BackgroundElement>* background = nullptr;

		public:
			Renderer(std::pair<int,int> res, ObjectManager* m): width(res.first), height(res.second), oManager(m)
			{
			
			}
			
			void setBackground(std::vector<BackgroundElement>* b)
			{
				this->background = b;
			}

			void initResourceManager() {
				this->rManager = ResourceManager::getSingleton();
			}

			void initShader() {
				this->shaderProgram = new Shader();

				this->shaderProgram->doShaders(VERT, FRAG);

				this->shaderProgram->addAttribute("vertexPosition");
				this->shaderProgram->addAttribute("vertexColor");
				this->shaderProgram->addAttribute("vertexUV");

				this->shaderProgram->linkShaders();
			} 

			void initCamera() {
				this->camera = new Camera2d(width, height);

				GLint pLocation = this->shaderProgram->getUniformLocation("P");
				glm::mat4 cameraMatrix = this->camera->getCameraMatrix();
				glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));
			}

			void spriteBatchInit() {
				this->sceneBatch = new SpriteBatch;
				this->objecBatch = new SpriteBatch;

				this->sceneBatch->init();
				this->objecBatch->init();
			}

			void createWindow()
			{
				if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
					throw "error:    SDL_init";
			}

			void showWindow() {
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

			void finalizeWindow() {
				SDL_DestroyWindow(this->window);
				SDL_Quit();
			}

			void render() {
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

			void renderLevel() {
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

			void renderObjects() {
				this->camera->update();
				//this->camera->setPosition(glm::vec2(0,0));
				this->camera->setPosition(this->camera->screenToWorld(glm::vec2(0, 0)));
			}
		};

		class Game
		{
			ObjectManager* manager = nullptr;
			FpsLimiter* limiter = nullptr;
			bool playing = false;
			float time = 0, fps = 0;

		public:
			Game(ObjectManager* m):
				manager(m),
				limiter(new FpsLimiter())
			{
				this->limiter->init(60);
			}

			void run()
			{
				this->playing = true;
				while (this->playing)
				{
					this->limiter->begin();
					{
						this->draw();

						this->time += 0.01f;
					}
					this->fps = this->limiter->end();

					static int frameCounter = 0;
					frameCounter++;
					if (frameCounter == 100) {
						std::cout << "fps: " << this->fps << std::endl;
						frameCounter = 0;
					}
				}
			
			}

			void stop()
			{
				this->playing=false;
			}

			void draw() {
				this->manager->renderer->render();
			}
		};

	private:
		bool OnScene = false;
		long counter = 0;
		std::map<ObjectID, Object*> objects;
		std::map<SceneID, std::vector<ObjectID>> sceneObjects;

		Relay* relay = nullptr;
		Renderer* renderer = nullptr;
		Game* game = nullptr;

		ObjectManager() {
			this->relay = Relay::getRelay();
			this->relay->registerManager(this);
		}

		void addScene(SceneID s)
		{
			if (this->renderer == nullptr)
			{
				this->renderer = new Renderer(this->relay->relayGetResolution(), this);
				this->game = new Game(this);
			}
			this->sceneObjects.emplace(s,std::vector<ObjectID>());
		}

		void deleteScene(SceneID s)
		{
			if (this->sceneObjects.erase(s) != 0)
			{
				s.scene->finalize();
				delete s.scene;
			}
		}

		bool isOnScene()
		{
			return this->OnScene;
		}

		void showScene(SceneID s)
		{
			auto sceneObjectsIt = this->sceneObjects.find(s);
			if (sceneObjectsIt == this->sceneObjects.end()) throw std::runtime_error("Scene not Loaded");
			s.scene->onDraw();
			this->OnScene = true;

			this->renderer->createWindow();
			this->renderer->showWindow();

			this->renderer->initShader();
			this->renderer->initResourceManager();
			this->renderer->spriteBatchInit();
			this->renderer->initCamera();

			this->renderer->setBackground(&s.scene->getBackground());

			this->game->run();
		}

		void swapScene(SceneID s)
		{

		}
		
		std::vector<BackgroundElement>& getSceneData(SceneID s)
		{
			return s.scene->getBackground();
		}

	public:
		static ObjectManager* getManager(){
			static ObjectManager* manager = new ObjectManager();
			return manager; //Can be converted to ARC later.
		}

		void interrupt()
		{
			if (this->game)
			{
				this->game->stop();
			}
		}

		Object::ID addObject(Object* o)
		{
			ObjectID id(counter++);
			this->objects.insert(std::make_pair(id,o));
			return id;
		}

		Object::ID addObject(Object* o, Scene::ID s)
		{
			ObjectID id(counter++);
			this->objects.emplace(id, o);
			auto ObjectVectorIt = this->sceneObjects.find(s);
			if (ObjectVectorIt != this->sceneObjects.end())
			{
				ObjectVectorIt->second.emplace_back(id);
			}
			else
			{
				throw std::runtime_error("Scene does not exist"); //Todo: replace
			}
			return id;
		}
		
		void bindObject(Object::ID o, Scene::ID s) {
			auto ObjectVectorIt = this->sceneObjects.find(s);
			if (ObjectVectorIt != this->sceneObjects.end())
			{
				ObjectVectorIt->second.emplace_back(o);
			}
			else
			{
				throw std::runtime_error("Scene does not exist");
			}
		}

		void unbindObject(Object::ID o, Scene::ID s)
		{
			auto objectVectorIt = this->sceneObjects.find(s);
			if (objectVectorIt != this->sceneObjects.end())
			{
				auto objectIt = std::find(objectVectorIt->second.begin(), objectVectorIt->second.end(),o);
				if (objectIt != objectVectorIt->second.end())
				{
					objectVectorIt->second.erase(objectIt);
				}
			}
		}

		void update(ObjectID id,const Action& action);
		void finalize()
		{}
    };
    
}

#endif /* sge_object_manager_h */
