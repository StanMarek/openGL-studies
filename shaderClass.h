#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H
#define BUFFER_SIZE 512

#include <GL/glew.h>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>

/*
Reads content of shader files like
vertices shader,
fragment shader
param - name or path to shader file
return - shader converted to string
*/
std::string getShaderFileContent(const char* filename);

/*
varaibles - self described
methods - self described
*/
class Shader
{
public:
	GLuint ID;

	Shader(const char* vertexFile, const char* fragmentFile);

	void Activate();
	void Delete();
};

#endif
