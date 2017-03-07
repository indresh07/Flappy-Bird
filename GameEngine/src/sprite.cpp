#include "sprite.h"
#include<ResourceManager.h>

namespace gameEngine{

    sprite::sprite()
    {
        _vboID = 0;
    }

    sprite::~sprite()
    {
        if(_vboID != 0)
            glDeleteBuffers(1, &_vboID);
    }

    void sprite::init(float x, float y, float width, float height, std::string texturePath){

        _x = x;
        _y = y;
        _width = width;
        _height = height;

        _texture = ResourceManager::getTexture(texturePath);

        if(_vboID == 0)
            glGenBuffers(1, &_vboID);
        //genrates n ID(s) and assign them to array of unsigned integer variables

        vertex point[6];

        //first triangle
        point[0].setVertex(0.9f, 0.8f, 0.79f, 1.0f, x + width, y + height,  1.0f, 1.0f);

        point[1].setVertex(1.0f, 0.4f, 0.5, 1.0f, x, y + height, 0.0f, 1.0f);

        point[2].setVertex(1.0f, 0.9f, 0.4f, 1.0f, x, y, 0.0f, 0.0f);

        //second triangle
        point[3].setVertex(0.86f, 0.91f, 0.88f, 1.0f, x, y, 0.0f, 0.0f );

        point[4].setVertex(0.9f, 0.7f, 0.9f, 1.0f, x + width, y, 1.0f, 0.0f);

        point[5].setVertex(0.9f, 0.8f, 0.79f, 1.0f, x + width, y + height, 1.0f, 1.0f);

        //binds object to the target buffer
        glBindBuffer(GL_ARRAY_BUFFER, _vboID);
        //uploads data to the target buffer
        //takes target, size of data, data , usage.
        //usage can be stresam or static or dynamic. draw or read or copy
        glBufferData(GL_ARRAY_BUFFER, sizeof(point), point, GL_STATIC_DRAW);
        //unbinds the oubject from the target buffer
        glBindBuffer(GL_ARRAY_BUFFER, 0);


    }
    void sprite::draw(){
        //binds texture to target
        glBindTexture(GL_TEXTURE_2D, _texture.id);
        //binds the vbo to buffer
        glBindBuffer(GL_ARRAY_BUFFER, _vboID);
        //enables generic vertex attribute array [i]
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);

        //uploads data to the array
        //takes in index, no. of sub variables, type of variable, normalized,size of variable, offset
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, position));
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_TRUE, sizeof(vertex), (void*)offsetof(vertex, color));
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, uv));
        //sets what is to  be drawn, from index, to index
        glDrawArrays(GL_TRIANGLES, 0, 6);

         //disables generic vertex attribute array [i]
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(2);
        //unbinds the target buffer
        glBindBuffer(GL_ARRAY_BUFFER, 0);

    }
}
