#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include <GL/glew.h>
#include "VBOClass.h"

class VertexArrayObject
{
public:
	GLuint ID;

	VertexArrayObject();

	void Bind();
	void Unbind();
};

#endif