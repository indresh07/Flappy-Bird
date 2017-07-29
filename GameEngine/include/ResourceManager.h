#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include "TextureCache.h"
#include <string>
namespace gameEngine{

    class ResourceManager
    {
        public:
            static GLtexture getTexture(std::string texturePath);
        protected:
        private:
            static TextureCache _textureCache;
    };
}
#endif // RESOURCEMANAGER_H
