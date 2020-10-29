#pragma once

#include <vector>

#include <SDL2\SDL.h>
#include <GL\glew.h>

#include "Sprite.h"
#include "GLProgram.h"
#include "Window.h"
#include "Camera2D.h"
#include "InputManager.h"

enum class GameState{
  PLAY, EXIT
};

class MainGame{
  int width;
  int height;
  InputManager inputManager;
  GLProgram glProgram;
  Camera2D camera2D;
  Window window;
  std::vector<Sprite> sprites;
  void processInput();
  void handleInput();
  void init();
  void initShaders();
  float time;
  const float CAMERA_SPEED = 20.0f;
  const float SCALE_SPEED = 0.1f;
public:
  MainGame();
  ~MainGame();
  GameState gameState;
  void run();
  void draw();
  void update();
};