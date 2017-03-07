#include "Window.h"
#include<iostream>
#include<Errors.h>
#include<glew.h>

namespace gameEngine{
    Window::Window()
    {
        //ctor
    }

    Window::~Window()
    {
        //dtor
    }

    int Window::create(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlags ){

        Uint32 flags = SDL_WINDOW_OPENGL;

        if(currentFlags & INVISIBLE)
            flags |= SDL_WINDOW_HIDDEN;

        if(currentFlags & FULLSCREEN)
            flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;

        if(currentFlags & BORDERLESS)
            flags |= SDL_WINDOW_BORDERLESS;

        //creats a native window of desired dimension and type i.e flag
        _window = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, flags);
        //X.c_str() return  pinter the string X

        if(_window == nullptr)
            fatalError("window could not be created!");

        //creats a background or environment for operations
        SDL_GLContext glcontext = SDL_GL_CreateContext(_window);

        if(glcontext == nullptr)
            fatalError("SDL_GL context could not be created!");

        //Initialzes glew for use
        GLenum error = glewInit();

        if(error != GLEW_OK)
            fatalError("Could not initialize glew!");


        //sets the background color for the  window. If not called the default color is black. RGBA format
        glClearColor(0.76f, 0.76f, 0.96f, 1.0f);

        //enables  the alpha i.e to set the transparency for background of drawn texture. Its black otherwise
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        //switches on VSync (Visual Synchronization) i.e frame rate = refresh rate of display
        SDL_GL_SetSwapInterval(1);
        std::cout<<"OpenGL Version "<<glGetString(GL_VERSION)<<std::endl;

        return 0;
    }

    //Facilitate the double buffer function
    void Window::swapBuffers(){
        SDL_GL_SwapWindow(_window);
    }
}
