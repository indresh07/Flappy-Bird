#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <glm/glm.hpp>

#include "../../GameEngine/include/Errors.h"
#include "../../GameEngine/include/spriteBatch.h"
#include "../../GameEngine/include/textures.h"
#include "Block.h"
class Map
{
    public:
        //load map
        Map();
        virtual ~Map();

        void init();

        void draw();
        int getPointCharacteristic(glm::vec2 position);

        void update();
    protected:
    private:

        std::vector<std::string> _mapData;
        int _blockSize;
        int _endPos;
        block _block[5];
        gameEngine::GLtexture _textureB;
        gameEngine::spriteBatch _spriteBatch;



};

#endif // MAP_H
