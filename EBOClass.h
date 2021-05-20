#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include <GL/glew.h>

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