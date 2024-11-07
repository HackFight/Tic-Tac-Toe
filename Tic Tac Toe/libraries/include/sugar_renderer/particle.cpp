#include"particle.h"

Particle::Particle()
{
	Renderer& renderer = Renderer::Get();
	renderer.transformations = glm::mat4(1.0f);
}

void Particle::Update()
{
	Particle::Position += Particle::Velocity * (float)Engine::Get().deltaTime;
	Particle::Velocity += Particle::Acceleration * (float)Engine::Get().deltaTime;
	Particle::Acceleration = glm::vec2(0.0f, 0.0f);
}

void Particle::Draw(Shader& s)
{
	//Don't forget to activate shader and bind vao before
	Renderer& renderer = Renderer::Get();
	Shader* shader = &s;

	(*shader).set4f("color", Particle::Color.r, Particle::Color.g, Particle::Color.b, Particle::Color.a);

	renderer.objectMatrix = glm::mat4(1.0f);

	renderer.objectMatrix = glm::translate(renderer.objectMatrix, glm::vec3(Particle::Position, 0.0f));   //Move it to the GameObject position
	renderer.objectMatrix = glm::scale(renderer.objectMatrix, glm::vec3(Particle::Scale, 0.0f));          //Scale the GameObject
	renderer.transformations = renderer.projection * renderer.objectMatrix;

	Particle::transShaderLoc = glGetUniformLocation((*shader).ID, "transformations");
	glUniformMatrix4fv(transShaderLoc, 1, GL_FALSE, glm::value_ptr(renderer.transformations));

	glDrawArrays(GL_TRIANGLES, 0, 3);
	//Don't forget to unbinf VAO after
}