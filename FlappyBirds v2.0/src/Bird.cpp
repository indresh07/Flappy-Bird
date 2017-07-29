#include "../include/Bird.h"

Bird::Bird() : _birdSize(64), _count(0), _cameraSpeed(13), _score(0.0f), flag(0)
{

}

Bird::~Bird()
{
    //dtor
}

void Bird::init(){

    _color.r = 255;
    _color.g = 255;
    _color.b = 255;
    _color.a = 255;

    _position = glm::vec4(-_birdSize/2, -_birdSize/2, _birdSize, _birdSize);
    _uv = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);

    _texture[0] = gameEngine::ResourceManager::getTexture("textures/bird/frame-1.png");
    _texture[1] = gameEngine::ResourceManager::getTexture("textures/bird/frame-2.png");
    _texture[2] = gameEngine::ResourceManager::getTexture("textures/bird/frame-3.png");
    _texture[3] = gameEngine::ResourceManager::getTexture("textures/bird/frame-4.png");
    _texture[4] = gameEngine::ResourceManager::getTexture("textures/bird/frame-5.png");
    _texture[5] = gameEngine::ResourceManager::getTexture("textures/bird/frame-6.png");
    _texture[6] = gameEngine::ResourceManager::getTexture("textures/bird/frame-7.png");
    _texture[7] = gameEngine::ResourceManager::getTexture("textures/bird/frame-8.png");
    _texture[8] = gameEngine::ResourceManager::getTexture("textures/bird/frame-9.png");
}

int Bird::draw(){

    static int frame = 0;
    if(frame == 72)
        frame = 0;

    _spriteBird.init();
    _spriteBird.begin();
    if(flag){
        _position.y += _cameraSpeed - (1.0f) * _count++;
        _position.x += 4.0f;
        _score += 0.5;
    }
    _spriteBird.draw(_position, _uv, 0.0f, _texture[(frame++/8) % 9].id, _color);
    _spriteBird.end();
    _spriteBird.renderBatch();

    return flag;

}

void Bird::update(){
    _count = 0;
    flag = 1;
}

void Bird::setPosition(glm::vec2 position){
    _position.x = position.x;
    _position.y = position.y;
}
