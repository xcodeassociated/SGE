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
#include <glm/detail/type_vec4.hpp>
#include <GL/glew.h>
#include <vector>

#include "sge_glyph_type.hpp"
#include "sge_glyph.hpp"
#include "sge_render_batch.hpp"

namespace SGE
{
    
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
