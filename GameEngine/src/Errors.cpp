#include "Errors.h"
namespace gameEngine{
    void fatalError(std::string errorString){
        std::cout<<errorString<<std::endl;
        std::cout<<"Enter any key to quit...";
        SDL_Quit();


    }
}
