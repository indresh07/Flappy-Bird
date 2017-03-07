#include "mainGame.h"

void gotoxy( int x, int y ){
    COORD p = { x, y };
    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), p );
}

mainGame::mainGame() : _screenWidth(1024), _screenHeight(768), _status(gameState::PLAY), flag(0)
{
    //ctor
}

mainGame::~mainGame()
{
}

void mainGame::run(){

    initSystems();

    gameloop();

    SDL_Quit();

}

void mainGame::initSystems(){

    gameEngine::init();
    _window.create("FLOPPY BIRDS v1.0.0", _screenWidth, _screenHeight, 0);
    _camera.init(_screenWidth, _screenHeight);
    _bird.init();
    _fps.init(90.0f);
    _maps.init();
    initShaders();
}

void mainGame::initShaders(){

    _shader.compileShader("C:/Users/Razor/Documents/Codeblocks_projects/FlappyBirds v2.0/shaders/shader.vs","C:/Users/Razor/Documents/Codeblocks_projects/FlappyBirds v2.0/shaders/shader.fs");
    _shader.addAttrib("vertexPosition");
    _shader.addAttrib("color");
    _shader.addAttrib("uv");
    _shader.linkShader();
}

void mainGame::gameloop(){

    static int count = 0;

    while(_status == gameState::PLAY){

        _fps.begin();
        processInput();
        _camera.setPosition(_camera.getPosition() - glm::vec2(4.0f * flag, 0));
        _camera.update();
        draw();
        fps = _fps.end();
        if(count++ ==  10){
            gotoxy(0,1);
            std::cout<<"FPS : "<< fps;
            count = 0;
        }
        gotoxy(0,2);
        std::cout<<"SCORE : "<<(int)_bird.getScore();
    }

}

void mainGame::processInput(){

    SDL_Event event;

    while(SDL_PollEvent(&event)){
        switch(event.type){

            case SDL_QUIT :
                _status = gameState::EXIT;
                break;

            case SDL_MOUSEBUTTONDOWN :
                _inputManager.keyPress(event.button.button);
                break;

            case SDL_MOUSEBUTTONUP :
                _inputManager.keyRelease(event.button.button);
                break;

            case SDL_KEYDOWN :
                _inputManager.keyPress(event.key.keysym.sym);
                break;

            case SDL_KEYUP :
                _inputManager.keyRelease(event.key.keysym.sym);
                break;
        }

        if(_inputManager.isKeyPressed(SDLK_ESCAPE))
            _status = gameState::EXIT;

        if(_inputManager.isKeyPressed(SDL_BUTTON_LEFT) || _inputManager.isKeyPressed(SDLK_UP)){
            if(_bird.getPosition().y < 358)
                _bird.update();
        }
    }


    if(_bird.getPosition().y < -361)
        _status = gameState::EXIT;

    if(_maps.getPointCharacteristic(_bird.getPosition()))
        _status = gameState::EXIT;

    if(flag)
        _maps.update();


}

void mainGame::draw(){

    glClearDepth(1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _shader.use();
    glActiveTexture(GL_TEXTURE0);

    GLuint sLocation = _shader.getUniformLocation("mySampler");
    glUniform1i(sLocation, 0);

    GLuint pLocation = _shader.getUniformLocation("projMatrix");
    glm::mat4 cameraMatrix = _camera.getCameraMatrix();
    glUniformMatrix4fv(pLocation, 1, GL_FALSE, &cameraMatrix[0][0]);

    _maps.draw();
    flag = _bird.draw();

    _shader.unuse();

    _window.swapBuffers();


}
