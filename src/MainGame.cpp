#include "MainGame.h"
#include <iostream>

using namespace std;

//Private

void MainGame::processInput(){
  SDL_Event event;
  while(SDL_PollEvent(&event)){
    switch(event.type){
      case SDL_QUIT:
        gameState = GameState::EXIT;
        break;
      case SDL_MOUSEMOTION:
        cout << "X: " << event.motion.x << " Y: " << event.motion.y << endl;
        break;
    }
  }
}

//Public

MainGame::MainGame(): window(nullptr), width(800), height(600),
                      gameState(GameState::PLAY){

}
MainGame::~MainGame(){

}
void MainGame::init(){
  window = SDL_CreateWindow("Clase 01", SDL_WINDOWPOS_CENTERED,
  SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);

  if(window == nullptr){
    //TODO: Mostrar error de SDL
  }
  SDL_GLContext glContext = SDL_GL_CreateContext(window);

  GLenum error = glewInit();
  if(error != GLEW_OK){
    //TODO: Mostrar error de Glew
  }
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  glClearColor(.0f, .0f, .1f, .1f);
}
void MainGame::run(){
  init();
  //TODO SPRITE
  update();
}
void MainGame::update(){
  while(gameState != GameState::EXIT){
    processInput();
    draw();
  }
}
void MainGame::draw(){
  glClearDepth(1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  //TODO: Update sprite
  SDL_GL_SwapWindow(window);
}