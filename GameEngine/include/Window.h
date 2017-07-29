#ifndef WINDOW_H
#define WINDOW_H
#include <string>
#include <SDL2/SDL.h>
namespace gameEngine{

    enum windowFlags {INVISIBLE = 0x1 , FULLSCREEN = 0x2, BORDERLESS = 0x4};

    class Window
    {
        public:
            Window();
            virtual ~Window();

            int create(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlags );

            void swapBuffers();
            int getScreenHeight(){ return _screenHeight; }
            int getScreenWidth(){ return _screenWidth; }
        protected:
        private:
            SDL_Window* _window;

            int _screenHeight;
            int _screenWidth;
    };
}

#endif // WINDOW_H
