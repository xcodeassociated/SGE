//
//  SpriteBatch.hpp
//  SimpleGameEngine_xc_1
//
//  Created by Hamashy on 12.02.2016.
//  Copyright © 2016 Hamashy. All rights reserved.
//

#ifndef SpriteBatch_h
#define SpriteBatch_h

#include "../Sprite/sge_vertex.hpp"
#include "../Sprite/sge_sprite.hpp"
#include <glm/vec4.hpp>
#include <GL/glew.h>
#include <vector>

#include "sge_glyph_type.hpp"
#include "sge_glyph.hpp"
#include "sge_render_batch.hpp"
#include "Object/sge_object.hpp"
#include <mat4x2.hpp>

namespace SGE
{
	class RealSpriteBatch
	{
	protected:
		size_t batchMaxCount = 0u;
		size_t batchMaxSize = 0u;
		GLTexture texture;
		GLuint program;
		GLuint sampler = 0;
		//Sprite Buffer Object
		GLuint SBO = 0;
		//UV Buffer Object
		GLuint UVBO = 0;
		//Matrix Uniform Buffer Object
		GLuint MUBO = 0;
		//Sprite Uniform Buffer Object
		GLuint SUBO = 0;
		GLuint VAO = 0;
		GLuint IBO = 0;
		std::vector<Object*> batchedObjects;
		std::vector<Sprite> spriteData;
		std::vector<std::pair<float, float>> uvData;
		const bool staticBatch;
		const bool uvBatch;
	public:
		RealSpriteBatch(GLuint program, size_t batchSize, bool uvBatch = false, bool staticBatch = false)
			: batchMaxCount(batchSize), batchMaxSize(batchSize * sizeof(Sprite)), program(program), staticBatch(staticBatch), uvBatch(uvBatch)
		{
			batchedObjects.reserve(batchSize);
			spriteData.reserve(batchSize);
			if(uvBatch)
			{
				uvData.reserve(batchSize * 4u);
			}
		}

		GLuint initalizeSampler(GLint wrap = GL_REPEAT,
								GLint magFilter = GL_LINEAR,
								GLint minFilter = GL_LINEAR_MIPMAP_LINEAR)
		{
			glGenSamplers(1, &this->sampler);
			glSamplerParameteri(this->sampler, GL_TEXTURE_WRAP_S, wrap);
			glSamplerParameteri(this->sampler, GL_TEXTURE_WRAP_T, wrap);
			glSamplerParameteri(this->sampler, GL_TEXTURE_MAG_FILTER, magFilter);
			glSamplerParameteri(this->sampler, GL_TEXTURE_MIN_FILTER, minFilter);
			return this->sampler;
		}

		GLuint initializeVAO(GLuint VAO = 0)
		{
			if(VAO != 0)
			{
				this->VAO = VAO;
			}
			else
			{
				constexpr GLuint posAttrib = 0;
				constexpr GLuint scaleAttrib = 1;
				constexpr GLuint rotAttrib = 2;
				constexpr GLuint layerAttrib = 3;
				constexpr GLuint uvAttrib = 4;
				glGenVertexArrays(1, &this->VAO);
				glBindVertexArray(this->VAO);
				glBindBuffer(GL_ARRAY_BUFFER, this->SBO);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->SBO);

				glEnableVertexArrayAttrib(this->VAO, posAttrib);
				glVertexAttribPointer(posAttrib, 2, GL_FLOAT, false, sizeof(Sprite), reinterpret_cast<GLvoid*>(offsetof(Sprite, position)));
				glVertexAttribDivisor(posAttrib, 6u);
				glEnableVertexArrayAttrib(this->VAO, scaleAttrib);
				glVertexAttribPointer(scaleAttrib, 2, GL_FLOAT, false, sizeof(Sprite), reinterpret_cast<GLvoid*>(offsetof(Sprite, scale)));
				glVertexAttribDivisor(scaleAttrib, 6u);
				glEnableVertexArrayAttrib(this->VAO, rotAttrib);
				glVertexAttribPointer(rotAttrib, 1, GL_FLOAT, false, sizeof(Sprite), reinterpret_cast<GLvoid*>(offsetof(Sprite, rotation)));
				glVertexAttribDivisor(rotAttrib, 6u);
				glEnableVertexArrayAttrib(this->VAO, layerAttrib);
				glVertexAttribPointer(layerAttrib, 1, GL_FLOAT, false, sizeof(Sprite), reinterpret_cast<GLvoid*>(offsetof(Sprite, layer)));
				glVertexAttribDivisor(layerAttrib, 6u);

				if(uvBatch)
				{
					glBindBuffer(GL_ARRAY_BUFFER, this->UVBO);
					glEnableVertexArrayAttrib(this->VAO, uvAttrib);
					glVertexAttribPointer(uvAttrib, 2, GL_FLOAT, false, 2, nullptr);
				}

				glUniform1i(glGetUniformLocation(this->program, "Sampler2D"), GL_TEXTURE0);
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, this->texture.id);
				glBindSampler(GL_TEXTURE0, this->sampler);

				glBindVertexArray(0);
				glBindBuffer(GL_ARRAY_BUFFER, 0);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			}
			return this->VAO;
		}

		GLuint initializeSBO(GLuint SBO = 0)
		{
			if(SBO != 0)
			{
				this->SBO = SBO;
			}
			else
			{
				glGenBuffers(1, &this->SBO);
				glBindBuffer(GL_ARRAY_BUFFER, this->SBO);
				glBufferData(GL_ARRAY_BUFFER, batchMaxSize, spriteData.data(), this->staticBatch ? GL_STATIC_DRAW : GL_STREAM_DRAW);
				glBindBuffer(GL_ARRAY_BUFFER, 0);
			}
			return this->SBO;
		}

		GLuint initializeUVBO(GLuint UVBO = 0)
		{
			if(UVBO != 0)
			{
				this->UVBO = UVBO;
			}
			else
			{
				glGenBuffers(1, &this->UVBO);
				glBindBuffer(GL_ARRAY_BUFFER, this->SBO);
				glBufferData(GL_ARRAY_BUFFER, batchMaxCount * 8u, uvData.data(), this->staticBatch ? GL_STATIC_DRAW : GL_STREAM_DRAW);
				glBindBuffer(GL_ARRAY_BUFFER, 0);
			}
			return this->SBO;
		}

		GLuint initializeIBO(GLuint IBO = 0)
		{
			if(IBO != 0)
			{
				this->IBO = IBO;
			}
			else
			{
				std::vector<GLushort> indexes;
				indexes.reserve(batchMaxCount * 6);
				for(GLushort i = 0; i != batchMaxCount; ++i)
				{
					indexes.push_back(i * 4 + 0);
					indexes.push_back(i * 4 + 1);
					indexes.push_back(i * 4 + 2);
					indexes.push_back(i * 4 + 2);
					indexes.push_back(i * 4 + 3);
					indexes.push_back(i * 4 + 0);
				}
				glGenBuffers(1, &this->IBO);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->SBO);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6u * batchMaxSize, indexes.data(), GL_STATIC_DRAW);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			}
			return this->IBO;
		}

		GLuint initalizeMUBO(GLuint MUBO = 0)
		{
			if(MUBO != 0)
			{
				this->MUBO = MUBO;
			}
			else
			{
				GLuint UBI = glGetUniformBlockIndex(this->program, "Matrix");
				glGenBuffers(1, &this->MUBO);
				constexpr GLuint UBB = 1;
				glUniformBlockBinding(this->program, UBI, UBB);
				glBindBuffer(GL_UNIFORM_BUFFER, this->MUBO);
				glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), nullptr, GL_STREAM_DRAW);
				glBindBuffer(GL_UNIFORM_BUFFER, 0);
				glBindBufferBase(GL_UNIFORM_BUFFER, UBB, this->MUBO);
			}
			return this->MUBO;
		}

		GLuint initalizeSUBO(GLuint SUBO = 0)
		{
			if(SUBO != 0)
			{
				this->SUBO = SUBO;
			}
			else
			{
				constexpr float halfWidth = 32.f, halfHeight = 32.f;
				glm::vec2 corners[4] = {
					glm::vec2{-halfWidth,  halfHeight},
					glm::vec2{-halfWidth, -halfHeight},
					glm::vec2{ halfWidth, -halfHeight},
					glm::vec2{ halfWidth,  halfHeight}
				};
				GLuint UBI = glGetUniformBlockIndex(this->program, "Sprite");
				glGenBuffers(1, &this->SUBO);
				constexpr GLuint UBB = 1;
				glUniformBlockBinding(this->program, UBI, UBB);
				glBindBuffer(GL_UNIFORM_BUFFER, this->SUBO);
				glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::vec2) * 4, nullptr, GL_STREAM_DRAW);
				glBindBuffer(GL_UNIFORM_BUFFER, 0);
				glBindBufferBase(GL_UNIFORM_BUFFER, UBB, this->SUBO);
			}
			return this->SUBO;
		}

		void initializeBatch()
		{
			if(this->SBO == 0)
			{
				this->initializeSBO();
			}
			if(uvBatch && this->UVBO == 0)
			{
				this->initializeUVBO();
			}
			if(this->IBO == 0)
			{
				this->initializeIBO();
			}
			if(this->sampler == 0)
			{
				initalizeSampler();
			}
			if(this->MUBO == 0)
			{
				initalizeMUBO();
			}
			if(this->SUBO == 0)
			{
				initalizeSUBO();
			}
			if(this->VAO == 0)
			{
				this->initializeVAO();
			}
		}

		void prepareBatch()
		{

		}
	};

	/**
	 * \brief
	 */
	class SpriteBatch
	{
	public:
		/**
		 * \brief
		 */
		SpriteBatch();

		/**
		 * \brief
		 */
		~SpriteBatch();

		/**
		 * \brief
		 */
		void init();

		/**
		 * \brief
		 * \param sortType
		 */
		void begin(GlyphSortType sortType = GlyphSortType::TEXTURE);

		/**
		 * \brief
		 */
		void end();

		/**
		 * \brief
		 * \param destRect
		 * \param uvRect
		 * \param texture
		 * \param depth
		 * \param color
		 */
		void draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const Color& color);

		/**
		 * \brief
		 */
		void renderBatch();

	private:
		/**
		 * \brief
		 */
		void createRenderBatches();

		/**
		 * \brief
		 */
		void createVertexArray();

		/**
		 * \brief
		 */
		void sortGlyphs();

		/**
		 * \brief
		 * \param a
		 * \param b
		 * \return
		 */
		static bool compareFrontToBack(Glyph* a, Glyph* b);

		/**
		 * \brief
		 * \param a
		 * \param b
		 * \return
		 */
		static bool compareBackToFront(Glyph* a, Glyph* b);

		/**
		 * \brief
		 * \param a
		 * \param b
		 * \return
		 */
		static bool compareTexture(Glyph* a, Glyph* b);

		/**
		 * \brief
		 */
		GLuint _vbo;
		/**
		 * \brief
		 */
		GLuint _vao;

		/**
		 * \brief
		 */
		GlyphSortType _sortType;

		/**
		 * \brief
		 */
		std::vector<Glyph*> _glyphs;
		/**
		 * \brief
		 */
		std::vector<RenderBatch> _renderBatches;
	};
}

#endif /* SpriteBatch_h */
