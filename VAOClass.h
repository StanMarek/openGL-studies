#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include <GL/glew.h>

/*
varaibles - self described
methods - self described
*/
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