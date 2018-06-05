//
//  SpriteBatch.hpp
//  SimpleGameEngine_xc_1
//
//  Created by Hamashy on 12.02.2016.
//  Copyright © 2016 Hamashy. All rights reserved.
//

#ifndef SpriteBatch_h
#define SpriteBatch_h

#include "sge_glyph_type.hpp"
#include "sge_glyph.hpp"
#include "sge_render_batch.hpp"

#include <glm/detail/type_vec4.hpp>
#include <GL/glew.h>
#include <vector>

namespace SGE
{
 
    class SpriteBatch
    {
		GLuint _vbo = 0;
		GLuint _vao = 0;
		GlyphSortType _sortType;

		std::vector<Glyph*> _glyphs;
		std::vector<RenderBatch> _renderBatches;

	    void createRenderBatches();

	    void createVertexArray();

	    void sortGlyphs();

	    static bool compareFrontToBack(Glyph* a, Glyph* b);

	    static bool compareBackToFront(Glyph* a, Glyph* b);

	    static bool compareTexture(Glyph* a, Glyph* b);

	public:
		void init();

		void begin(GlyphSortType sortType = GlyphSortType::TEXTURE);

		void end();

		void draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const Color& color);

		void renderBatch();
    };
}

#endif /* SpriteBatch_h */
