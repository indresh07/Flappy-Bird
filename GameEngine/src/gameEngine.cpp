#include <SDL2/SDL.h>
#include <GL/glew.h>
#include "../include/gameEngine.h"

namespace gameEngine{
    int init(){
        //Initializes all the subsystems eg. audio subsystem, timer subsystem, controller subsystem, etc.
        SDL_Init(SDL_INIT_EVERYTHING);
        //Enables various gl attributes. Here Double Buffering. This is also enables by default
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

        return 0;
    }
}
