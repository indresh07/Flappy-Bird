#include "../include/ResourceManager.h"
namespace gameEngine{
    TextureCache ResourceManager::_textureCache;

    //finds/creates the texture inthe texture cache and return its value
    GLtexture ResourceManager::getTexture(std::string texturePath){
        return _textureCache.getTexture(texturePath);
    }
}
