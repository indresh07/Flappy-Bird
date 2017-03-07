#include "Camera2D.h"
namespace gameEngine{
    Camera2D::Camera2D() :
        _needsMatrixUpdate(true),
        _screenHeight(1080),
        _screenWidth(1920),
        _scale(1.0f),
        _position(0.0f,0.0f),
        _cameraMatrix(1.0f),
        _orthoMatrix(1.0f)
    {
        //ctor
    }

    Camera2D::~Camera2D()
    {
        //dtor
    }

    void Camera2D::init(int screenWidth, int screenHeight){
        _screenWidth = screenWidth;
        _screenHeight = screenHeight;
        //creates a orthomatrix for conversion from screen coordinate system to desired coordinate system
        _orthoMatrix = glm::ortho(-(float)_screenWidth/2, (float)_screenWidth/2, -(float)_screenHeight/2, (float)_screenHeight/2);
    }

    void Camera2D::update(){

        if(_needsMatrixUpdate){
            glm::vec3 translate (_position.x, _position.y, 0.0f);
            //translates the camera to new position vec3 translate (which is in user coordinate system) and uses the orthomatrix to convert them into screen coordinates
            _cameraMatrix = glm::translate(_orthoMatrix, translate);

            glm::vec3 scale (_scale, _scale, 0.0f);
            //sets scale or magnification value for the camera
            _cameraMatrix = glm::scale(glm::mat4(1.0f),scale) * _cameraMatrix;
            _needsMatrixUpdate = false;
        }

    }

    glm::vec2 Camera2D::convertScreenToWorld(glm::vec2 screenCoords){

        screenCoords.x = _screenWidth - screenCoords.x;
        screenCoords = glm::vec2(_screenWidth,_screenHeight) - screenCoords;
        screenCoords -= glm::vec2((float)_screenWidth/2, (float)_screenHeight/2);
        screenCoords /= glm::vec2(_scale, _scale);
        screenCoords -= _position;
        return screenCoords;
    }
}
