#include "VAOClass.h"

VertexArrayObject::VertexArrayObject()
{
	glGenVertexArrays(1, &ID);
}

void VertexArrayObject::Bind()
{
	glBindVertexArray(ID);
}

void VertexArrayObject::Unbind()
{
	glBindVertexArray(0);
}

void VertexArrayObject::Delete()
{
	glDeleteVertexArrays(1, &ID);
}
