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
        inputManager.setMouseCoords(event.motion.x, event.motion.y);
        break;
      case SDL_KEYUP:
        inputManager.releaseKey(event.key.keysym.sym);
        break;
      case SDL_KEYDOWN:
        inputManager.pressKey(event.key.keysym.sym);
        break;
    }
  }
  handleInput();
}

void MainGame::handleInput(){
  if(inputManager.isKeyPressed(SDLK_w)){
    camera2D.setPosition(camera2D.getPosition() + glm::vec2(0.0, CAMERA_SPEED));
  }
  if(inputManager.isKeyPressed(SDLK_s)){
    camera2D.setPosition(camera2D.getPosition() + glm::vec2(0.0, -CAMERA_SPEED));
  }
  if(inputManager.isKeyPressed(SDLK_a)){
    camera2D.setPosition(camera2D.getPosition() + glm::vec2(-CAMERA_SPEED, 0.0));
  }
  if(inputManager.isKeyPressed(SDLK_d)){
    camera2D.setPosition(camera2D.getPosition() + glm::vec2(CAMERA_SPEED, 0.0));
  }
  if(inputManager.isKeyPressed(SDLK_q)){
    camera2D.setScale(camera2D.getScale() + SCALE_SPEED);
  }
  if(inputManager.isKeyPressed(SDLK_e)){
    camera2D.setScale(camera2D.getScale() - SCALE_SPEED);
  }
}

//Public

MainGame::MainGame(): width(800), height(600),
                      gameState(GameState::PLAY), time(0){
  camera2D.init(width, height);
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
  camera2D.update();
  update();
}
void MainGame::update(){
  while(gameState != GameState::EXIT){
    processInput();
    draw();
    camera2D.update();
  }
}
void MainGame::draw(){
  glClearDepth(1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glProgram.use();
  
  GLuint timeLocation = glProgram.getUniformLocation("time");
  GLuint imageLocation = glProgram.getUniformLocation("image");
  GLuint pLocation = glProgram.getUniformLocation("P");

  glUniform1f(timeLocation, time);
  glUniform1i(imageLocation, 0);

  time += 0.0002;

  glm::mat4 cameraMatrix = camera2D.getCameraMatrix();
  glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

  for(Sprite &sprite : sprites){
    sprite.draw();
  }
  
  glProgram.unuse();
  window.swapBuffer();
}
