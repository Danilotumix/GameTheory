#pragma once

#include <SDL2/SDL.h>
#include <gl/glew.h>
#include <string>

using namespace std;

enum WindowFlags{
    INVISIBLE,
    FULLSCREEN,
    BORDERLESS
};

class Window{
    SDL_Window* window;
    int screenWidth, screenHeight;
public:
    Window();
    ~Window();

    void swapBuffer();
    int getScreenWidth(){ return screenWidth; }
    int getScreenHeight(){ return screenHeight; }

    int create(string WindowName, int screenWidth, int screenHeight);
};