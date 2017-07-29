#include "../include/spriteBatch.h"
#include<algorithm>

namespace gameEngine{


    spriteBatch::spriteBatch() : _vbo(0), _vao(0)
    {
        //ctor
    }

    spriteBatch::~spriteBatch()
    {
        //dtor
    }

    void spriteBatch::init(){

        createVertexArray();

    }

    void spriteBatch::begin(glyphSortType sortType){

        _sortType = sortType;
        _renderBatches.clear();
        _glyphs.clear();
    }

    void spriteBatch::end(){

        sortGlyphs();
        createRenderBatches();
    }

    void spriteBatch::draw(const glm::vec4& destRect, const glm::vec4& uvRect,float depth, GLuint texture, const Color& col){

        glyph* newGlyph = new glyph;
        newGlyph->texture = texture;
        newGlyph->depth = depth;

        newGlyph->topLeft.setVertex(col.r, col.g, col.b, col.a, destRect.x, destRect.y, uvRect.x, uvRect.y);
        newGlyph->topRight.setVertex(col.r, col.g, col.b, col.a, destRect.x + destRect.z, destRect.y, uvRect.x + uvRect.z, uvRect.y);
        newGlyph->bottomLeft.setVertex(col.r, col.g, col.b, col.a, destRect.x, destRect.y + destRect.w, uvRect.x, uvRect.y + uvRect.w);
        newGlyph->bottomRight.setVertex(col.r, col.g, col.b, col.a, destRect.x + destRect.z, destRect.y + destRect.w, uvRect.x + uvRect.z, uvRect.y + uvRect.w);

        _glyphs.push_back(newGlyph);
    }

    void spriteBatch::renderBatch(){
        //binds the VAO to the current rendering array
        glBindVertexArray(_vao);

        for(int i = 0; i < _renderBatches.size(); i++){
            //bind the texture to the target texture array
            glBindTexture(GL_TEXTURE_2D, _renderBatches[i].texture);
            //what to draw, offset, no. of vertices
            glDrawArrays(GL_TRIANGLES, _renderBatches[i].offset, _renderBatches[i].nVertices);
        }

        glBindVertexArray(0);

    }

    void spriteBatch::createRenderBatches(){

        std::vector<vertex> vertices;
        vertices.resize( _glyphs.size() * 6);

        if(_glyphs.empty())
            return;

        int offset = 0;
        int cv = 0; //current vertex
        //pushes texture to the renderbatches vector
        //emplace_back does no t=require to create a new element of datatype of vector and the push it in the vector
        //it directly uses constructor parameters and takes care of rest of the things itself
        _renderBatches.emplace_back(offset, 6, _glyphs[0]->texture);

        vertices[cv++] = _glyphs[0]->topLeft;
        vertices[cv++] = _glyphs[0]->bottomLeft;
        vertices[cv++] = _glyphs[0]->bottomRight;
        vertices[cv++] = _glyphs[0]->bottomRight;
        vertices[cv++] = _glyphs[0]->topRight;
        vertices[cv++] = _glyphs[0]->topLeft;

        offset += 6;

        for(int cg = 1; cg < _glyphs.size(); cg++){

            if(_glyphs[cg]->texture != _glyphs[cg - 1]->texture)
                _renderBatches.emplace_back(offset, 6, _glyphs[cg]->texture);
            else
                _renderBatches.back().nVertices += 6;
                //x.back() returns reference ot the last element of vector
            vertices[cv++] = _glyphs[cg]->topLeft;
            vertices[cv++] = _glyphs[cg]->bottomLeft;
            vertices[cv++] = _glyphs[cg]->bottomRight;
            vertices[cv++] = _glyphs[cg]->bottomRight;
            vertices[cv++] = _glyphs[cg]->topRight;
            vertices[cv++] = _glyphs[cg]->topLeft;

            offset += 6;
        }
        //binds an VBO to the buffer array
        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
        //orphan the data (****google orphan****)
        //target, total size of array/vector, pointer to data,  data, usage
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertex), nullptr, GL_DYNAMIC_DRAW);
        //upload the orphaned data
        //target, offset, total size of array, pointer to data
        glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(vertex), vertices.data());
        //x.data() return pointer the underlying array serving as element storage

        glBindBuffer(GL_ARRAY_BUFFER, 0);


    }

    void spriteBatch::createVertexArray(){

        //creates n IDs for VAO if no ID is already assigned
        if(_vao == 0)
            glGenVertexArrays(1, &_vao);
        //Binds an object to current rendering array
        glBindVertexArray(_vao);
        //creates n IDs for VBO if no ID is already assigned
        if(_vbo == 0)
            glGenBuffers(1, &_vbo);
        //Binds the VBO to target buffer
        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
        //enables generic vertex attribute array [i]
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);
        //uploads data to the vetex attribute array [i]
        //index, no. of sub variables, type, normalized, size of variable, offset
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, position));
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_TRUE, sizeof(vertex), (void*)offsetof(vertex, color));
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, uv));
        //unbinds vertex array
        glBindVertexArray(0);
    }

    void spriteBatch::sortGlyphs(){

        switch(_sortType){
            //sorts the glyphs according tom ode
            case glyphSortType::BACK2FRONT :
                //stable_sort syntax: starting of array, ending  of array, boolean operation to be applied for sorting
                std::stable_sort(_glyphs.begin(), _glyphs.end(), compareBackToFront);
                break;

            case glyphSortType::FRONT2BACK :
                std::stable_sort(_glyphs.begin(), _glyphs.end(), compareFrontToBack);
                break;

            case glyphSortType::TEXTURE :
                std::stable_sort(_glyphs.begin(), _glyphs.end(), compareTexture);
                break;

        }

    }

    bool spriteBatch::compareFrontToBack (glyph* a, glyph* b){
        return (a->depth < b->depth);
    }

    bool spriteBatch::compareBackToFront (glyph* a, glyph* b){
        return (a->depth > b->depth);
    }

    bool spriteBatch::compareTexture (glyph* a, glyph* b){
        return (a->texture < b->texture);
    }
}
