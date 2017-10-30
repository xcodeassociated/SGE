//
//  SpriteBatch.hpp
//  SimpleGameEngine_xc_1
//
//  Created by Hamashy on 12.02.2016.
//  Copyright © 2016 Hamashy. All rights reserved.
//

#ifndef SpriteBatch_h
#define SpriteBatch_h

#include <algorithm>
#include <sge_vertex.hpp>
#include <glm/detail/type_vec4.hpp>
#include <GL/glew.h>
#include <vector>

#include "sge_glyph_type.hpp"
#include "sge_glyph.hpp"
#include "sge_render_batch.hpp"

namespace SGE {
    
    class SpriteBatch
    {
    public:
	    SpriteBatch();

	    ~SpriteBatch();

	    void init();

	    void begin(GlyphSortType sortType = GlyphSortType::TEXTURE);

	    void end();

        void draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const Color& color){
            Glyph* newGlyph = new Glyph;
            newGlyph->texture = texture;
            newGlyph->depth = depth;
            
            newGlyph->topLeft.color = color;
            newGlyph->topLeft.setPosition(destRect.x, destRect.y + destRect.w);
            newGlyph->topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);
            
            newGlyph->bottomLeft.color = color;
            newGlyph->bottomLeft.setPosition(destRect.x, destRect.y);
            newGlyph->bottomLeft.setUV(uvRect.x, uvRect.y);
            
            newGlyph->bottomRight.color = color;
            newGlyph->bottomRight.setPosition(destRect.x + destRect.z, destRect.y);
            newGlyph->bottomRight.setUV(uvRect.x + uvRect.z, uvRect.y);
            
            newGlyph->topRight.color = color;
            newGlyph->topRight.setPosition(destRect.x + destRect.z, destRect.y + destRect.w);
            newGlyph->topRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);
            
            _glyphs.push_back(newGlyph);
        }

	    void renderBatch();

    private:
	    void createRenderBatches();

	    void createVertexArray();

	    void sortGlyphs();

	    static bool compareFrontToBack(Glyph* a, Glyph* b);

	    static bool compareBackToFront(Glyph* a, Glyph* b);

	    static bool compareTexture(Glyph* a, Glyph* b);

        GLuint _vbo;
        GLuint _vao;
        
        GlyphSortType _sortType;
        
        std::vector<Glyph*> _glyphs;
        std::vector<RenderBatch> _renderBatches;
    };
}

#endif /* SpriteBatch_h */
