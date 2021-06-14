#ifndef EXTERNAL_FUNCTIONS_H
#define EXTERNAL_FUNCTIONS_H

#include <vector>
#include <GL/glew.h>
#include <SFML/Window.hpp>
#include "VBOClass.h"
#include <fstream>
#include <string>
#include <istream>
#include <sstream>
#include <iostream>
#include <vector>
#include "globalVariables.h"


typedef unsigned int uint;

namespace functions {
	void cube(GLuint buffer);
	void cube(VertexBufferObject& vbo);
	void setCamera(GLint _uView);
	void circle(int verticesSize);
	void setCameraMouse(GLint uniView, float elapsedTime, const sf::Window& window);
	void setCameraKeyboard(GLint uniView, float elapsedTime);
	void stereoProjection(GLuint shaderProgram_, float _left, float _right, float _bottom, float _top, float _near, float _far, float _zero_plane, float _dist, float _eye);
	void generateCubeTextures(int primitive, uint texture1, uint texture2, uint texture3);
	void loadModelObj(int& punkty_, const char* filename, int buffer);
	void loadModelObj_EBO(int& punkty_, const char* filename, int buffer_vbo, int buffer_ebo);
	bool loadModelOBJNormalsCoord(int& punkty_, const char* filename, int buffer, std::vector<std::vector<int>>& objects);
	void bindTextureModel(GLint _primitive, std::vector<unsigned int>& _textures, std::vector<std::vector<int>>& _objects);
}

#endif // !EXTERNAL_FUNCTIONS_H