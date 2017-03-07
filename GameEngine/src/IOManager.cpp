#include "IOManager.h"
#include<fstream>

namespace gameEngine{
    bool IOManager::readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer){

        std::ifstream file(filePath, std::ios::binary);
        if(file.fail()){
            //prints the error occur during opening file
            perror(filePath.c_str());
            return false;
        }

        //seek to end

        file.seekg(0, std::ios::end);

        int filesize = file.tellg();                            //tells no. bytes from previous position of cursor

        //seek to begining

        file.seekg(0, std::ios::beg);

        //removes any header in file size

        filesize -= file.tellg();
        //resizes a vector
        buffer.resize(filesize);
        file.read((char*)&(buffer[0]), filesize);
        file.close();

        return true;

    }
}
