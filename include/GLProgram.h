#pragma once

#include <GL\glew.h>
#include <string>

using namespace std;

class GLProgram {
  GLuint programID;
  GLuint fragmentShaderID;
  GLuint vertexShaderID;
  int numAttribute;

  void compileShader(const string& shaderPath, GLuint id);
public:
  GLProgram();
  ~GLProgram();
  void compileShaders(const string& vertexShaderFilePath,
                      const string& fragmentShaderFilePath);
                      
  void AddAttribute(const string& attributeName);
  void use();
  GLuint getUniformLocation(const string& name);
  void unuse();
  void linkShader();
};