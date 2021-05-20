#include "EBOClass.h"

ElementBufferObject::ElementBufferObject()
{
	glGenBuffers(1, &ID);
}

void ElementBufferObject::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void ElementBufferObject::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void ElementBufferObject::Delete()
{
	glDeleteBuffers(1, &ID);
}
