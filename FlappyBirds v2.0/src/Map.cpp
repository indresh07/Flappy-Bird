#include "../include/Map.h"
#include "../../GameEngine/include/ResourceManager.h"
#include <ctime>

Map::Map() : _endPos(-512)
{

}


Map::~Map()
{
    //dtor
}

void Map::init(){
     _blockSize = 24;
    _textureB = gameEngine::ResourceManager::getTexture("FlappyBirds v2.0/textures/building/boundary.png");

    srand(time(0));
    for(int i = 0; i < 5; i++){
        _block[i].x = rand() % 16;
        _block[i].startPos = glm::vec2(300 + i * 256, -385 );
    }
}

void Map::draw(){

     _spriteBatch.init();
    _spriteBatch.begin();

    glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
    gameEngine::Color color;
    color.r = 255;
    color.g = 255;
    color.b = 255;
    color.a = 255;
    glm::vec4 pos;

    for(int x = _endPos; x < _endPos + 1024; x += 24 ){
        pos = glm::vec4(x, _block[0].startPos.y, 24, 24);
        _spriteBatch.draw(pos, uv, 0.0f, _textureB.id, color);
        _spriteBatch.draw(pos + glm::vec4(0, 31*24,0,0), uv, 0.0f, _textureB.id, color);
    }

    for(int j = 0; j < 5; j++){
        for(int i = 1; i < 5 + _block[j].x; i++){
            pos = glm::vec4( _block[j].startPos.x, _block[j].startPos.y + (i * 24), 24, 24);
            _spriteBatch.draw( pos, uv, 0.0f, _textureB.id, color);
            _spriteBatch.draw( pos + glm::vec4(24, 0, 0, 0), uv, 0.0f, _textureB.id, color);
        }
    }

    for(int j = 0; j < 5; j++){
        for(int i = 12 + _block[j].x; i < 31; i++){
            pos = glm::vec4( _block[j].startPos.x, _block[j].startPos.y + (i * 24), 24, 24);
            _spriteBatch.draw( pos, uv, 0.0f, _textureB.id, color);
            _spriteBatch.draw( pos + glm::vec4(24, 0, 0, 0), uv, 0.0f, _textureB.id, color);
        }
    }

    _spriteBatch.end();
    _spriteBatch.renderBatch();
}

int Map::getPointCharacteristic(glm::vec2 position){

    for(int i = 0; i < 5; i++){
        //LEFT-BOTTOM
        if(position.x + 16 > _block[i].startPos.x && position.x + 16 < (_block[i].startPos.x + 48)){
            if((position.y + 14> _block[i].startPos.y + (5 + _block[i].x)* 24) && (position.y + 14 < _block[i].startPos.y + (12 + _block[i].x)* 24))
                return 0;
            else
                return 1;
        }
        //LEFT-TOP
        if(position.x + 5 > _block[i].startPos.x && position.x + 5 < (_block[i].startPos.x + 48)){
            if((position.y + 64 > _block[i].startPos.y + (5 + _block[i].x)* 24) && (position.y + 64 < _block[i].startPos.y + (12 + _block[i].x)* 24))
                return 0;
            else
                return 1;
        }
        //RIGHT-BOTTOM
        if(position.x + 51 > _block[i].startPos.x && position.x + 51< (_block[i].startPos.x + 48)){
            if((position.y + 14> _block[i].startPos.y + (5 + _block[i].x)* 24) && (position.y + 14 < _block[i].startPos.y + (12 + _block[i].x)* 24))
                return 0;
            else
                return 1;
        }
        //RIGHT-TOP
        if(position.x + 64> _block[i].startPos.x && position.x + 64< (_block[i].startPos.x + 48)){
            if((position.y + 64> _block[i].startPos.y + (5 + _block[i].x)* 24) && (position.y + 64 < _block[i].startPos.y + (12 + _block[i].x)* 24))
                return 0;
            else
                return 1;
        }
    }

    return 0;
}

void Map::update(){

    _endPos += 3.0f;

    if(_block[0].startPos.x + 48 < _endPos){
        for(int i = 0; i < 4; i++){
            _block[i].x = _block[i+1].x;
            _block[i].startPos = _block[i+1].startPos;
        }

        _block[4].x = rand() % 16;
        _block[4].startPos += glm::vec2(216,0);
    }

}
