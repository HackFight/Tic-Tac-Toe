#ifndef RENDERER_H
#define RENDERER_H

#include <iostream>
#include<glad/glad.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"

class Renderer
{
public:
	glm::mat4 projection = glm::ortho(-5.0f, 5.0f, -5.0f, 5.0f, 0.0f, 10.0f);
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 transformations = glm::mat4(1.0f);
	glm::mat4 objectMatrix = glm::mat4(1.0f);

	float proj_width = 10.0f, proj_height = 10.0f;

private:
	int transShaderLoc = 0;

public:
	void SetProjectionSize(float width, float height, float depth);
	static void Draw(Shader& shader, glm::mat4& transformations, VAO& vao, GLsizeiptr size) { return Get().IDraw(shader, transformations, vao, size); }
	static void DrawArrays(Shader& shader, glm::mat4& transformations, VAO& vao, GLsizeiptr size, GLint first, GLsizei count) { return Get().IDrawArrays(shader, transformations, vao, size, first, count); }
	static void ClearScreen() { return Get().IClearScreen(); }
	static void ClearScreen(glm::vec4 color) { return Get().IClearScreen(color); }
	static void ClearScreen(float r, float g, float b, float a) { return Get().IClearScreen(r, g, b, a); }

private:
	void IDraw(Shader& shader, glm::mat4& transformations, VAO& vao, GLsizeiptr size);
	void IDrawArrays(Shader& shader, glm::mat4& transformations, VAO& vao, GLsizeiptr size, GLint first, GLsizei count);
	void IClearScreen();
	void IClearScreen(glm::vec4 color);
	void IClearScreen(float r, float g, float b, float a);


public:
	Renderer(const Renderer&) = delete;

	static Renderer& Get()
	{
		static Renderer instance;
		return instance;
	}

private:
	Renderer() {}
};
#endif