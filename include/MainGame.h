#ifndef _MAINGAME_H_
#define _MAINGAME_H_

#include <SDL2\SDL.h>
#include <GL\glew.h>

#include "Sprite.h"

enum class GameState{
  PLAY, EXIT
};

class MainGame{
  int width;
  int height;
  SDL_Window* window;
  Sprite sprite;
  void init();
  void processInput();
public:
  MainGame();
  ~MainGame();
  GameState gameState;
  void run();
  void draw();
  void update();
};

#endif
