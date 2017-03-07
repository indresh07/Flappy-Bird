#ifndef TIMING_H
#define TIMING_H

namespace gameEngine{

    class FPSlimiter{
        public:

            FPSlimiter();

            void init(float maxFPS);

            void setMaxFPS(float maxFPS);

            void begin();

            float end();

        private:

            void calculateFPS();

            float _maxFPS;
            unsigned int _startTick;
             float _fps;



    };



}

#endif // TIMING_H
