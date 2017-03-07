#ifndef CAMERA2D_H
#define CAMERA2D_H

#include<glm.hpp>
#include<gtc/matrix_transform.hpp>
#include<iostream>

namespace gameEngine{
    class Camera2D
    {
        public:
            Camera2D();
            virtual ~Camera2D();

            void init(int screenWidth, int screenHeight);

            void update();

            glm::vec2 convertScreenToWorld(glm::vec2 screenCoords);

            //sets
            void setPosition(glm::vec2 newPosition) { _position = newPosition; _needsMatrixUpdate = true;}
            void setScale(float newScale) {_scale = newScale; _needsMatrixUpdate = true;}

            //get
            glm::vec2 getPosition() { return _position;}
            glm::mat4 getCameraMatrix() {return _cameraMatrix;}
            float getScale() {return _scale;}
        protected:
        private:
            bool _needsMatrixUpdate;
            int _screenHeight;
            int _screenWidth;
            float _scale;
            glm::vec2 _position;
            glm::mat4 _cameraMatrix;
            glm::mat4 _orthoMatrix;

    };
}
#endif // CAMERA2D_H
