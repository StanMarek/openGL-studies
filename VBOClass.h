#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include <GL/glew.h>

class VertexBufferObject
{
public:
	GLuint ID;

	VertexBufferObject();
	//VertexBufferObject(GLfloat* vertices, GLsizeiptr size);

	void Bind();
	void Unbind();
	void Delete();
};

#endif // !VBO_CLASS_H
