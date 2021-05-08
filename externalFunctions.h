#ifndef EXTERNAL_FUNCTIONS_H
#define EXTERNAL_FUNCTIONS_H

#include <GL/glew.h>
#include <SFML/Window.hpp>
#include "globalVariables.h"
typedef unsigned int uint;

namespace functions {
	void cube(int buffer);
	void setCamera(GLint _uView);
	void circle(int verticesSize);
	void setCameraMouse(GLint uniView, float elapsedTime, const sf::Window& window);
	void setCameraKeyboard(GLint uniView, float elapsedTime);
	void stereoProjection(GLuint shaderProgram_, float _left, float _right, float _bottom, float _top, float _near, float _far, float _zero_plane, float _dist, float _eye);
	void generateCubeTextures(int primitive, uint texture1, uint texture2, uint texture3);
}

#endif // !EXTERNAL_FUNCTIONS_H