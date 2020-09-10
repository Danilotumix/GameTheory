#ifndef _VERTEX_H_
#define _VERTEX_H_

#include <GL\glew.h>

struct Position{
  float x;
  float y;
};

struct Vertex {
  Position position;

  void setPosition(float x, float y){
    position.x = x;
    position.y = y;
  }
};

#endif
