#include "VBO.h"

VBO::VBO(GLfloat* vertices, GLsizeiptr size)
{
	ObjectsManager::AddObject(this);
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

void VBO::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::Delete()
{
	Logger::log(DEBUG, "Deleted a VBO");
	glDeleteBuffers(1, &ID);
}