#ifndef PARTICLE_H
#define PARTICLE_H

#include<iostream>
#include<glad/glad.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include"VAO.h"
#include"shaderClass.h"
#include"chocolate_engine/engine.h"

struct Particle
{
	glm::vec2 Scale = glm::vec2(1.0f, 1.0f);
	glm::vec2 Position = glm::vec2(0.0f, 0.0f);
	float Rotation = 0.0f;
	glm::vec2 Velocity = glm::vec2(0.0f, 0.0f);
	glm::vec2 Acceleration = glm::vec2(0.0f, 0.0f);
	float Mass = 0.001f;

	glm::vec4 Color = glm::vec4(1.0f ,1.0f, 1.0f, 1.0f);

private:
	int transShaderLoc = 0;

public:
	Particle();

	void Update();
	void Draw(Shader& shader);

};

#endif