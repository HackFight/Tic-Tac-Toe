#include"gameObject.h"

GameObject::GameObject(Shader& shader, VAO& vao, GLsizeiptr indicesSize)
{
	GameObject::shader = &shader;
	GameObject::vao = &vao;
	GameObject::indicesSize = indicesSize;
}

void GameObject::Draw()
{
	Renderer& renderer = Renderer::Get();

	renderer.objectMatrix = glm::mat4(1.0f);
	renderer.transformations = glm::mat4(1.0f);

	renderer.objectMatrix = glm::translate(renderer.objectMatrix, glm::vec3(GameObject::Position, 0.0f));   //Move it to the GameObject position
	renderer.objectMatrix = glm::scale(renderer.objectMatrix, glm::vec3(GameObject::Scale, 0.0f));          //Scale the GameObject
	renderer.transformations = renderer.projection * renderer.objectMatrix;

	Renderer::Draw(*GameObject::shader, renderer.transformations, (*GameObject::vao), indicesSize);
}

void GameObject::DrawArray(GLint first, GLsizei count)
{
	Renderer& renderer = Renderer::Get();

	renderer.objectMatrix = glm::mat4(1.0f);

	renderer.objectMatrix = glm::translate(renderer.objectMatrix, glm::vec3(GameObject::Position, 0.0f));   //Move it to the GameObject position
	renderer.objectMatrix = glm::scale(renderer.objectMatrix, glm::vec3(GameObject::Scale, 0.0f));          //Scale the GameObject
	renderer.transformations = renderer.projection * renderer.objectMatrix;

	Renderer::DrawArrays(*GameObject::shader, renderer.transformations, (*GameObject::vao), indicesSize, 0, 3);
}

void GameObject::DrawColor(glm::vec4 color)
{
	Renderer& renderer = Renderer::Get();

	(*GameObject::shader).Activate();

	(*GameObject::shader).set4f("color", color.r, color.g, color.b, color.a);

	renderer.objectMatrix = glm::mat4(1.0f);
	renderer.transformations = glm::mat4(1.0f);

	renderer.objectMatrix = glm::translate(renderer.objectMatrix, glm::vec3(GameObject::Position, 0.0f));   //Move it to the GameObject position
	renderer.objectMatrix = glm::scale(renderer.objectMatrix, glm::vec3(GameObject::Scale, 0.0f));          //Scale the GameObject
	renderer.transformations = Renderer::Get().projection * renderer.objectMatrix;

	Renderer::Draw(*GameObject::shader, renderer.transformations, (*GameObject::vao), indicesSize);
}

void GameObject::DrawLitTexture(int numberOfLights, glm::vec4 lightColor[], glm::vec3 lightPos[], int tex0Unit, GLenum baseEnum, Texture base, int normalsUnit, GLenum normalsEnum, Texture normals)
{
	Renderer& renderer = Renderer::Get();

	(*GameObject::shader).Activate();

	(*GameObject::shader).setInt("tex0", tex0Unit);
	(*GameObject::shader).setInt("normals", normalsUnit);

	(*GameObject::shader).set3f("crntPos", GameObject::Position.x, GameObject::Position.y, 1.0f);
	(*GameObject::shader).setFloat("ambient", 0.1f);

	for (GLuint i = 0; i < numberOfLights; i++)
	{
		std::string number = std::to_string(i);

		(*GameObject::shader).set3f("pointLights[" + number + "].position", lightPos[i].x, lightPos[i].y, lightPos[i].z);
		(*GameObject::shader).set4f("pointLights[" + number + "].color", lightColor[i].x, lightColor[i].y, lightColor[i].z, lightColor[i].w);
	}

	glActiveTexture(baseEnum);
	base.Bind();
	glActiveTexture(normalsEnum);
	normals.Bind();

	renderer.objectMatrix = glm::mat4(1.0f);
	renderer.transformations = glm::mat4(1.0f);

	renderer.objectMatrix = glm::translate(renderer.objectMatrix, glm::vec3(GameObject::Position, 0.0f));   //Move it to the GameObject position
	renderer.objectMatrix = glm::scale(renderer.objectMatrix, glm::vec3(GameObject::Scale, 0.0f));          //Scale the GameObject
	renderer.transformations = Renderer::Get().projection * renderer.objectMatrix;

	Renderer::Draw(*GameObject::shader, renderer.transformations, (*GameObject::vao), indicesSize);
}