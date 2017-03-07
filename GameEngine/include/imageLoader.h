#ifndef IMAGELOADER_H
#define IMAGELOADER_H

#include<string>
#include<textures.h>
namespace gameEngine{

    class imageLoader
    {
        public:
            static GLtexture loadPNG(std::string filepath);

        protected:
        private:
    };
}

#endif // IMAGELOADER_H
