#ifndef SPRITE_H
#define SPRITE_H

#include<iostream>
#include<glew.h>
#include<vertex.h>
#include<textures.h>
namespace gameEngine{

    class sprite
    {
        public:
            sprite();
            virtual ~sprite();

            void init(float x, float y, float width, float height, std::string texturePath);

            void draw();
        protected:
        private:

            float _x;
            float _y;
            float _width;
            float _height;

            GLtexture _texture;

            GLuint _vboID;          //virtual buffer object id
    };
}
#endif // SPRITE_H
