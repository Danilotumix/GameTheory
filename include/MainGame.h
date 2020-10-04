#pragma once

#include <vector>

#include <SDL2\SDL.h>
#include <GL\glew.h>

#include "Sprite.h"
#include "GLProgram.h"
#include "Window.h"

enum class GameState{
  PLAY, EXIT
};

class MainGame{
  int width;
  int height;
  GLProgram glProgram;
  Window window;
  std::vector<Sprite> sprites;
  void processInput();
  void init();
  void initShaders();
  float time;
public:
  MainGame();
  ~MainGame();
  GameState gameState;
  void run();
  void draw();
  void update();
};