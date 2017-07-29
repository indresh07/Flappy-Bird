#ifndef MAINGAME_H
#define MAINGAME_H

#include <vector>
#include <ncurses.h>
#include <fstream>

#include "../../GameEngine/include/gameEngine.h"
#include "../../GameEngine/include/Window.h"
#include "../../GameEngine/include/GLSLprog.h"
#include "../../GameEngine/include/Camera2D.h"
#include "../../GameEngine/include/timing.h"
#include "../../GameEngine/include/InputManager.h"

#include "Bird.h"
#include "Map.h"

enum class gameState {PLAY, EXIT};

class mainGame
{
    public:
        mainGame();
        virtual ~mainGame();

        void initSystems();
        void initShaders();
        void run();
        void draw();
        void gameloop();
        void processInput();

    protected:
    private:
        int _screenWidth;
        int _screenHeight;
        float fps;
        int flag;

        gameState _status;
        Bird _bird;
        Map _maps;

        gameEngine::Window _window;
        gameEngine::GLSLprog _shader;
        gameEngine::Camera2D _camera;
        gameEngine::FPSlimiter _fps;
        InputManager _inputManager;


};

#endif // MAINGAME_H
