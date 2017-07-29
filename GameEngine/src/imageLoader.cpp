#include "../include/imageLoader.h"
#include "../include/picoPNG.h"
#include "../include/IOManager.h"
#include "../include/Errors.h"
namespace gameEngine{

    GLtexture imageLoader::loadPNG(std::string filepath){

        GLtexture texture = {};

        std::vector<unsigned char> in;
        std::vector<unsigned char> out;

        if(IOManager::readFileToBuffer(filepath, in) == false)
            fatalError("Unable to load PNG file from " + filepath);

        unsigned long width, height;

        int errorCode = decodePNG(out, width, height, &(in[0]), in.size());

        if(errorCode != 0)
            fatalError("deodePNG failed to work due to error : " + errorCode);

        //generates n texture ID(s). Here 1 texture id is generated and assigned to texture.id
        glGenTextures(1, &(texture.id));
        //bounds the texture using texture ID to the target
        glBindTexture(GL_TEXTURE_2D, texture.id);
        //takes target, level, internal format, width, height, border size, format, pointer to output array and process the target texture and writes processed data to ouput array
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &(out[0]));

        //sets parameter for currently bound texture
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        //generated mipmaping for target texture
        //mipmaping means it generates high resolution image for the parts that are close to camera and low resolution image for points that are father away
        glGenerateMipmap(GL_TEXTURE_2D);
        //Unbinds  the target texture
        glBindTexture(GL_TEXTURE_2D, 0);

        texture.height = height;
        texture.width = width;

        return texture;
    }
}
