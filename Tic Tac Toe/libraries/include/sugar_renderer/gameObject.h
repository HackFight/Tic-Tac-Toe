#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include<iostream>
#include<glad/glad.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include"renderer.h"
#include"texture.h"

class GameObject
{
public:
	glm::vec2 Scale = glm::vec2(1.0f, 1.0f);
	glm::vec2 Position = glm::vec2(0.0f, 0.0f);
	float Rotation = 0.0f;

	VAO* vao;
	Shader* shader;
	GLsizeiptr indicesSize;

	GameObject(Shader& shader, VAO& vao, GLsizeiptr indicesSize);

	void Draw();
	void DrawArray(GLint first, GLsizei count);
	void DrawColor(glm::vec4 color);
	void DrawLitTexture(int numberOfLights, glm::vec4 lightColor[], glm::vec3 lightPos[], int tex0Unit, GLenum baseEnum, Texture base, int normalsUnit, GLenum normalsEnum, Texture normals);
};

#endif