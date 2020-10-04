#include "GLProgram.h"
#include "Error.h"

#include <fstream>
#include <vector>

GLProgram::GLProgram(): programID(0), 
                        vertexShaderID(0), 
                        fragmentShaderID(0),
                        numAttribute(0){

    
}

GLProgram::~GLProgram(){

}

void GLProgram::compileShaders(const string& vertexShaderFilePath,
                               const string& fragmentShaderFilePath){
    programID = glCreateProgram();
    vertexShaderID = glCreateShader(GL_VERTEX_SHADER);

    if(vertexShaderID == 0){
        fatalError("Can't create VERTEX_SHADER");
    }
    
    fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    if(fragmentShaderID == 0){
        fatalError("Can't create FRAGMENT_SHADER");
    }

    compileShader(vertexShaderFilePath, vertexShaderID);
    compileShader(fragmentShaderFilePath, fragmentShaderID);
}

void GLProgram::AddAttribute(const string& attributeName){
    glBindAttribLocation(programID, numAttribute++, attributeName.c_str());
}

void GLProgram::use(){
    glUseProgram(programID);

    for(size_t i = 0; i < numAttribute; ++i){
        glEnableVertexAttribArray(i);
    }
}

GLuint GLProgram::getUniformLocation(const string& name){
    GLuint location = glGetUniformLocation(programID, name.c_str());
    if(location == GL_INVALID_ENUM){
        fatalError("Uniform " + name + " not found in shader");
    }
    return location;
}

void GLProgram::unuse(){
    glUseProgram(programID);

    for(size_t i = 0; i < numAttribute; ++i){
        glDisableVertexAttribArray(i);
    }
}

void GLProgram::compileShader(const string& shaderPath, GLuint id){
    string fileContent = "";
    string line = "";

    ifstream shaderFile(shaderPath);
    if(shaderFile.fail()){
        fatalError("Could not open " + shaderPath);
    }
    while(getline(shaderFile, line)){
        fileContent += line + "\n";
    }
    shaderFile.close();
    const char* contents = fileContent.c_str();
    glShaderSource(id, 1, &contents, nullptr);
    glCompileShader(id);

    GLint isCompiled = 0;

    glGetShaderiv(id, GL_COMPILE_STATUS, &isCompiled);

    if(isCompiled == GL_FALSE){
        GLint maxLength = 0;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);
        std::vector<GLchar> errorLog(maxLength);
        glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);
        fatalError("Couldn't compile shaders " + printf("%s",&(errorLog[0])));
        glDeleteShader(id);
        return;
    }
}

void GLProgram::linkShader(){
    glAttachShader(programID, vertexShaderID);
    glAttachShader(programID, fragmentShaderID);
    glLinkProgram(programID);

    GLint isLinked = 0;
    glGetProgramiv(programID, GL_LINK_STATUS, (int*)&isLinked);

    if(isLinked == GL_FALSE){
        GLint maxLength = 0;
        glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &maxLength);
        std::vector<GLchar> infoLog(maxLength);
        glGetProgramInfoLog(programID, maxLength, &maxLength, &infoLog[0]);
        glDeleteProgram(programID);
        fatalError("Couldn't link shaders " + printf("%s",&(infoLog[0])));
        glDeleteShader(vertexShaderID);
        glDeleteShader(fragmentShaderID);
        return;
    }
    glDetachShader(programID, vertexShaderID);
    glDetachShader(programID, fragmentShaderID);
    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);
}