#ifndef BIRD_H
#define BIRD_H

#include <glm/glm.hpp>
#include <iostream>
//#include <windows.h>

#include "../../GameEngine/include/textures.h"
#include "../../GameEngine/include/ResourceManager.h"
#include "../../GameEngine/include/spriteBatch.h"


class Bird
{
    public:
        Bird();
        virtual ~Bird();

        void init();
        int draw();
        void update();
        void setPosition(glm::vec2 position);

        //getters
        glm::vec2 getPosition() {return glm::vec2(_position.x, _position.y);}
        float getScore(){return _score;}
    protected:
    private:
        int _birdSize;
        int _count;
        int _cameraSpeed;
        float _score;
        int flag;

        glm::vec4 _position;
        glm::vec4 _uv;
        gameEngine::Color _color;

        gameEngine::GLtexture _texture[9];
        gameEngine::spriteBatch _spriteBird;
};

#endif // BIRD_H
