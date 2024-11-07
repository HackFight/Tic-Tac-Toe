#ifndef EBO_H
#define EBO_H

#include<glad/glad.h>
#include<chocolate_engine/objectsManager.h>

class EBO : public Object
{
public:
	GLuint ID;
	EBO(GLuint* indices, GLsizeiptr size);

	void Bind();
	void Unbind();
	void Delete() override;
};

#endif
