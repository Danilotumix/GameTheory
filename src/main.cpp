#include <iostream>

#include "MainGame.h"

using namespace std;

int main(int argc, char ** argv){
  MainGame game;
  game.run();
  SDL_Init(SDL_INIT_EVERYTHING);
  return 0;
}
