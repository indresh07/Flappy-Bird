#ifndef TEXTURECACHE_H
#define TEXTURECACHE_H

#include <map>
#include <string>
#include "textures.h"

namespace gameEngine{
    class TextureCache
    {
        public:
            TextureCache();
            virtual ~TextureCache();

            GLtexture getTexture( std::string texturePath);
        protected:
        private:
            //map contains a key and a value. key is used as a quantity to arrange data.
            std::map< std::string, GLtexture> _textureMap;
    };
}
#endif // TEXTURECACHE_H
