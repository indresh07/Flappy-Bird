#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <unordered_map>
#include <glm/glm.hpp>

class InputManager
{
    public:
        InputManager();
        virtual ~InputManager();

        void keyPress(unsigned int keyID);
        void keyRelease(unsigned int keyID);
        void setMouseCoords(float x, float y);
        bool isKeyPressed(unsigned int keyID);

        glm::vec2 getMouseCoords() {return _mouseCoords;}

    protected:
    private:

        std::unordered_map<unsigned int, bool> _keyMap;
        glm::vec2 _mouseCoords;


};

#endif // INPUTMANAGER_H
