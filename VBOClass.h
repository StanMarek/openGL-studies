#ifndef VBO_CLAS_H
#define VBO_CLASS_H

#include <GL/glew.h>

class VertexBufferObject
{
public:
	GLuint ID;

	VertexBufferObject();

	void Bind();
	void Unbind();
};

#endif // !VBO_CLAS_H
