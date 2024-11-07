#ifndef VBO_H
#define VBO_H

#include<glad/glad.h>
#include<chocolate_engine/objectsManager.h>

class VBO : public Object
{
public:
	GLuint ID;
	VBO(GLfloat* vertices, GLsizeiptr size);

	void Bind();
	void Unbind();
	void Delete() override;
};

#endif
