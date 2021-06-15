#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include <GL/glew.h>

/*
varaibles - self described
methods - self described
*/
class ElementBufferObject
{
public:
	GLuint ID;

	ElementBufferObject();

	void Bind();
	void Unbind();
	void Delete();
};

#endif