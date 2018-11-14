#ifndef SGE_RENDERER_HPP
#define SGE_RENDERER_HPP

#include <string>
#include <vector>
#include <map>
#include "SpriteBatch/sge_sprite_batch.hpp"
#include "ResourceManager/sge_resource_manager.hpp"
#include "Shaders/sge_shader.hpp"
#include <algorithm>
#include "WindowManager/sge_window_manager.hpp"
#include "CameraHandler/sge_camera_handler.hpp"
#include "Game/sge_game.hpp"


namespace SGE
{
	class CameraHandler;
	class WindowManager;
	class Scene;

	class BatchRenderer
	{
		struct SceneBatches
		{
			size_t batchNames = 0u;
			//Single IBO, vertices are expected to be processed in same order every time
			GLuint IBO = 0;
			std::vector<RealSpriteBatch*> batches;
			std::map<size_t, RealSpriteBatch*> batchLookup;
			bool dirty = false;
			~SceneBatches()
			{
				for(RealSpriteBatch* b: batches)
				{
					delete b;
				}
			}
		};
		std::map<Scene*, SceneBatches*> batchedScenes;
		std::map<GLuint, GLuint> programMUBOs;
		ResourceManager* resManager = nullptr;
		CameraHandler* camHandler = nullptr;
		WindowManager* winManager = nullptr;
		SceneBatches* cur = nullptr;
	public:
		BatchRenderer(CameraHandler* camHandler, ResourceManager* resManager, WindowManager* winManager)
			: resManager(resManager), camHandler(camHandler), winManager(winManager)
		{}
		~BatchRenderer()
		{
			for(auto batches: batchedScenes)
			{
				delete batches.second;
			}
		}
		void sortBatches()
		{
			std::stable_sort(cur->batches.begin(), cur->batches.end(), [](RealSpriteBatch* lhs, RealSpriteBatch* rhs)
			{
				return lhs->texture.id < rhs->texture.id;
			});
			std::stable_sort(cur->batches.begin(), cur->batches.end(), [](RealSpriteBatch* lhs, RealSpriteBatch* rhs)
			{
				return lhs->program < rhs->program;
			});
			cur->dirty = false;
		}

		size_t addBatch(RealSpriteBatch* batch)
		{
			cur->dirty = true;
			cur->batches.push_back(batch);
			decltype(cur->batchLookup.insert(std::make_pair(0u, batch))) res;
			size_t batchName;
			do
			{
				batchName = cur->batchNames++;
				res = cur->batchLookup.insert(std::make_pair(batchName, batch));
			}
			while(res.second == false);
			return batchName;
		}

		size_t newBatch(GLuint programID, const std::string& texture, size_t batchSize, bool uvBatch = false, bool staticBatch = false)
		{
			RealSpriteBatch* batch = new RealSpriteBatch(programID, batchSize, uvBatch, staticBatch);
			GLuint MUBO = programMUBOs[programID];
			if(MUBO == 0)
			{
				programMUBOs[programID] = batch->initalizeMUBO();
			}
			else
			{
				batch->initalizeMUBO(MUBO);
			}
			batch->texture = this->resManager->getTexture((Game::getGame()->getGamePath() + texture).c_str());
			return this->addBatch(batch);
		}

		void deleteBatch(size_t batchName)
		{
			auto res = cur->batchLookup.find(batchName);
			if(res != cur->batchLookup.end())
			{
				cur->batches.erase(std::find(cur->batches.begin(), cur->batches.end(), res->second));
				cur->batchLookup.erase(res);
			}
		}

		RealSpriteBatch* getBatch(size_t batchName)
		{
			auto res = cur->batchLookup.find(batchName);
			if(res != cur->batchLookup.end())
			{
				return res->second;
			}
			return nullptr;
		}

		static GLuint getProgramID(const std::string& vertPath, const std::string& fragPath)
		{
			Shader program;
			if(vertPath.empty() || fragPath.empty())
				throw std::runtime_error{"vert or frag missing"};

			program.compileShaders(vertPath.c_str(), fragPath.c_str());
			program.linkShaders();
			return program.getProgramId();
		}

		void updateCamera()
		{
			this->camHandler->updateCamera();
			for(auto pair: this->programMUBOs)
			{
				glm::mat4 cameraMatrix = this->camHandler->getCameraMatrix();
				glBindBuffer(GL_UNIFORM_BUFFER, pair.second);
				glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), &cameraMatrix);
				glBindBuffer(GL_UNIFORM_BUFFER, 0);
			}
		}

		void setScene(Scene* scene)
		{
			auto res = this->batchedScenes.find(scene);
			if(res == this->batchedScenes.end())
			{
				this->cur = (this->batchedScenes[scene] = new SceneBatches());
			}
			else
			{
				this->cur = this->batchedScenes[scene];
			}
		}

		void render(Scene* scene)
		{
			glClearDepth(1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			if(cur->dirty)
			{
				this->sortBatches();
			}
			//This assumes single camera matrix across all programs.
			this->updateCamera();
			GLuint programID = 0;
			GLuint textureID = 0;
			for(RealSpriteBatch* batch : cur->batches)
			{
				if(programID != batch->program)
				{
					programID = batch->program;
					glUseProgram(programID);
				}
				if(textureID != batch->texture.id)
				{
					textureID = batch->texture.id;
					glActiveTexture(GL_TEXTURE0);
					glBindTexture(GL_TEXTURE_2D, textureID);
				}
				batch->prepareBatch();
				batch->renderBatch();
			}
			this->winManager->swapWindow();
		}
	};

	class Renderer
	{
		/**
		 * \brief
		 */
		int width = 0;
		/**
		 * \brief
		 */
		int height = 0;
		/**
		 * \brief
		 */
		ResourceManager* resourceManager = nullptr;
		/**
		 * \brief
		 */
		SpriteBatch* sceneBatch = nullptr;
		/**
		 * \brief
		 */
		SpriteBatch* objectBatch = nullptr;
		/**
		 * \brief
		 */
		CameraHandler* camera_handler = nullptr;
		/**
		 * \brief
		 */
		Shader* shaderProgram = nullptr;
		/**
		 * \brief
		 */
		WindowManager* window_manager = nullptr;
		/**
		 * \brief
		 */
		Scene* current = nullptr;

		std::string vert = "";
		std::string frag = "";

		/**
		 * \brief
		 */
		void renderLevel();

		/**
		 * \brief
		 */
		void renderObjects();

	public:
		/**
		 * \brief
		 */
		Renderer(const std::string& _vert, const std::string& _frag, std::pair<int, int>,
				 WindowManager *, CameraHandler *, ResourceManager* resourceManager) noexcept;

		 /**
		  * \brief
		  */
		void initShader();

		/**
		 * \brief
		 */
		void spriteBatchInit();

		/**
		 * \brief
		 */
		void render(Scene* scene);

	};

}

#endif // !SGE_RENDERER_HPP
