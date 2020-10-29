#include "InputManager.h"

InputManager::InputManager(){

}

InputManager::~InputManager(){

}

void InputManager::setMouseCoords(float x, float y){
    mouseCoords.x = x;
    mouseCoords.y = y;
}

void InputManager::pressKey(unsigned int keyCode){
    keys[keyCode] = true;
}

void InputManager::releaseKey(unsigned int keyCode){
    keys[keyCode] = false;
}

bool InputManager::isKeyPressed(unsigned int keyCode){
    std::unordered_map<unsigned int, bool>::iterator it = keys.find(keyCode);
    if(it != keys.end()){
        return it->second;
    }

    return false;
}