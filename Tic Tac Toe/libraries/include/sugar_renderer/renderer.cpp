#include"renderer.h"

void Renderer::IDraw(Shader& shader, glm::mat4& transformations, VAO& vao, GLsizeiptr size)
{
	shader.Activate();

	Renderer::transShaderLoc = glGetUniformLocation(shader.ID, "transformations");
	glUniformMatrix4fv(transShaderLoc, 1, GL_FALSE, glm::value_ptr(transformations));

	vao.Bind();
	glDrawElements(GL_TRIANGLES, size / sizeof(int), GL_UNSIGNED_INT, 0);
	vao.Unbind();
}

void Renderer::IDrawArrays(Shader& shader, glm::mat4& transformations, VAO& vao, GLsizeiptr size, GLint first, GLsizei count)
{
	shader.Activate();

	Renderer::transShaderLoc = glGetUniformLocation(shader.ID, "transformations");
	glUniformMatrix4fv(transShaderLoc, 1, GL_FALSE, glm::value_ptr(transformations));

	vao.Bind();
	glDrawArrays(GL_TRIANGLES, first, count);
	vao.Unbind();
}

void Renderer::IClearScreen()
{
	glClearColor(0.11f, 0.09f, 0.12f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::IClearScreen(glm::vec4 color)
{
	glClearColor(color.r, color.g, color.b, color.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::IClearScreen(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::SetProjectionSize(float width, float height, float depth)
{
	Renderer::Get().projection = glm::ortho(-width/2.0f, width / 2.0f, -height/2.0f, height / 2.0f, 0.0f, depth);
	Renderer::Get().proj_height = height;
	Renderer::Get().proj_width = width;
}