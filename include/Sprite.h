#ifndef _SPRITE_H_
#define _SPRITE_H_

#include <GL\glew.h>


class Sprite{
private:
  float x;
  float y;
  int width;
  int height;
public:
  Sprite();
  ~Sprite();
  void init(float x, float y, int width, int height);
  void draw();
};

#endif
