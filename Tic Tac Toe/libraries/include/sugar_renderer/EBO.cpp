#include "EBO.h"

EBO::EBO(GLuint* indices, GLsizeiptr size)
{
	ObjectsManager::AddObject(this);
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

void EBO::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void EBO::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::Delete()
{
	Logger::log(DEBUG, "Deleted an EBO");
	glDeleteBuffers(1, &ID);
}