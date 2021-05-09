#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include <GL/glew.h>

class VertexArrayObject
{
public:
	GLuint ID;

	VertexArrayObject();

	void Bind();
	void Unbind();
	void Delete();
};

#endif