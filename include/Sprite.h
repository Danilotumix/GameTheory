#ifndef _SPRITE_H_
#define _SPRITE_H_

#include <GL\glew.h>

using namespace std;

class Sprite{
  float x;
  float y;
  int width;
  int height;
  GLuint vboID;
public:
  Sprite();
  ~Sprite();
  void init(float x, float y, int width, int height);
  void draw();
};

#endif
