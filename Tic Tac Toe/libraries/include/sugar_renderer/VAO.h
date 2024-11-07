#ifndef VAO_H
#define VAO_H

#include<glad/glad.h>
#include<chocolate_engine/objectsManager.h>
#include"VBO.h"


class VAO : public Object
{
public:
	GLuint ID;
	VAO();

	void LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
	void Bind();
	void Unbind();
	void Delete() override;
};


#endif