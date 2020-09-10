#ifndef _GLPROGRAM_H_
#define _GLPROGRAM_H_

#include <GL\glew.h>
#include <string>

using namespace std;

class GLProgram {
  GLuint programID;
  GLuint fragmentShaderID;
  GLuint vertexShaderID;

  void compileShader(const string& shaderPath, GLuint id);
public:
  GLProgram();
  ~GLProgram();
  void compileShaders(const string& vertexShaderFilePath,
                      const string& fragmentShaderFilePath
};

#endif
