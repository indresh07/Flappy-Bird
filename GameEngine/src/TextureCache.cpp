#include "TextureCache.h"
#include "imageLoader.h"
#include<iostream>
namespace gameEngine{
    TextureCache::TextureCache()
    {
        //ctor
    }

    TextureCache::~TextureCache()
    {
        //dtor
    }

    GLtexture TextureCache::getTexture( std::string texturepath){
        //finds the texture in  the map and return an iterator for the location
        //auto automatically creates a variable of mentioned name of the return datatype of function
        auto mit = _textureMap.find(texturepath);

        //checks if texture is not in the map
        if(mit == _textureMap.end()){

            GLtexture newTexture = imageLoader::loadPNG(texturepath);

            //loadsthe texture on map using pair
            //pair is like a structure containing two elements  of same or different data type
            _textureMap.insert(make_pair(texturepath, newTexture));

            return newTexture;
        }
        //if texture is already present in the map then return the value for the texture. first -> key, second -> value
        return mit->second;
    }
}
