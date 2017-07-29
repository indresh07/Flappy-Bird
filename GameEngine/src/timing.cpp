#include "../include/timing.h"
#include <SDL2/SDL.h>

namespace gameEngine{

    FPSlimiter::FPSlimiter(){

    }

    void FPSlimiter::init(float maxFPS){
        setMaxFPS(maxFPS);
    }

    void FPSlimiter::setMaxFPS(float maxFPS){
        _maxFPS = maxFPS;
    }

    void FPSlimiter::begin(){
        _startTick = SDL_GetTicks();


    }

    float FPSlimiter::end(){

        calculateFPS();

        float frameTicks = SDL_GetTicks() - _startTick;

        if(1000.0f / _maxFPS > frameTicks)
           SDL_Delay(1000.0f / _maxFPS - frameTicks);

        return _fps;
    }

    void FPSlimiter::calculateFPS(){

    static const int numSamples = 10;
    static float frameTimes[numSamples];
    static int currentFrame = 0;
    float frameTimeAvg = 0;
    int div;

    static float prevTicks = SDL_GetTicks();
    float currTicks;

    currTicks = SDL_GetTicks();


    frameTimes[currentFrame % numSamples] = currTicks - prevTicks;
    prevTicks = currTicks;

    if(currentFrame < numSamples)
        div = currentFrame;
    else
        div = numSamples;

    for(int i = 0; i < div; i++)
        frameTimeAvg += frameTimes[i];

    frameTimeAvg /= div;

    if(frameTimeAvg > 0)
        _fps = 1000.0f / frameTimeAvg;
    else
        _fps = 60.0f;

    currentFrame++;
    }
}
