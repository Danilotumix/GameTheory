#include "MainGame.h"
#include "Error.h"
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

MainGame::MainGame(): width(800), height(600),
                      gameState(GameState::PLAY), time(0){

}
MainGame::~MainGame(){

}

void MainGame::initShaders(){
  glProgram.compileShaders("./shaders/colorShaderVert.glsl",
                           "./shaders/colorShaderFrag.glsl");
  
  glProgram.AddAttribute("vertexPosition");
  glProgram.AddAttribute("vertexColor");
  glProgram.AddAttribute("vertexUV");
  glProgram.linkShader();
}

void MainGame::init(){
  sprites = vector<Sprite>(4);
  window.create("OOF", width, height);
  initShaders();
}
void MainGame::run(){
  init();
  sprites[0].init(-1,-1,1,1, "images/Yoshi.png");
  sprites[1].init(-1,0,1,1, "images/Mario.png");
  sprites[2].init(0,0,1,1, "images/Bowser.png");
  sprites[3].init(0,-1,1,1, "images/Kirby.png");
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
  glProgram.use();
  
  GLuint timeLocation = glProgram.getUniformLocation("time");
  GLuint imageLocation = glProgram.getUniformLocation("image");

  glUniform1f(timeLocation, time);
  glUniform1i(imageLocation, 0);

  time += 0.0002;

  for(Sprite &sprite : sprites){
    sprite.draw();
  }
  
  glProgram.unuse();
  window.swapBuffer();
}
