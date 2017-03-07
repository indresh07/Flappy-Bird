#ifndef SPRITEBATCH_H
#define SPRITEBATCH_H
#include<glew.h>
#include<glm.hpp>
#include<vertex.h>
#include<vector>

namespace gameEngine{

    enum glyphSortType{             //mode of sorting required
        NONE,
        FRONT2BACK,
        BACK2FRONT,
        TEXTURE
    };

    struct glyph{

        GLuint texture;

        float depth;

        vertex topLeft;
        vertex topRight;
        vertex bottomLeft;
        vertex bottomRight;

    };

    class RenderBatch{
        public :
            RenderBatch(GLuint Offset, GLuint NVertices, GLuint Texture) : offset(Offset), nVertices(NVertices), texture(Texture)
            {
            }
            GLuint offset;
            GLuint nVertices;
            GLuint texture;
    };

    class spriteBatch
    {
        public:
            spriteBatch();
            virtual ~spriteBatch();

            void init();
            //sets the mode of sorting and clears the reender batches and glyphs
            void begin(glyphSortType sortType = glyphSortType::TEXTURE);        //default parameter is TEXTURE
            //pre-render processes i.e sorting of glyphs and create batches
            void end();
            //updates the glyphs and push them into glyph vector
            void draw(const glm::vec4& destRect, const glm::vec4& uvRect, float depth, GLuint texture, const gameEngine::Color& col);
            //render the batch on the screen
            void renderBatch();
        protected:
        private:
            void createRenderBatches();
            void createVertexArray();
            void sortGlyphs();


            static  bool compareFrontToBack (glyph* a, glyph* b);
            static  bool compareBackToFront (glyph* a, glyph* b);
            static  bool compareTexture (glyph* a, glyph* b);

            GLuint _vbo;
            GLuint _vao;

            glyphSortType _sortType;

            std::vector<glyph* > _glyphs;
            std::vector<RenderBatch> _renderBatches;
    };
}

#endif // SPRITEBATCH_H
