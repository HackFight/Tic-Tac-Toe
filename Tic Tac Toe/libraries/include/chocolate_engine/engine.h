#ifndef ENGINE_H
#define ENGINE_H

#include<iostream>
#include<algorithm>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/norm.hpp>

#include<sugar_renderer/VAO.h>
#include<sugar_renderer/VBO.h>
#include<sugar_renderer/EBO.h>
#include<sugar_renderer/shaderClass.h>
#include<sugar_renderer/texture.h>
#include<sugar_renderer/renderer.h>
#include<sugar_renderer/particle.h>
#include<chocolate_engine/logger.h>
#include<chocolate_engine/input.h>

class Engine
{
public:
	//WINDOW
	GLFWwindow* window = glfwCreateWindow(600, 600, "Default", NULL, NULL);

	//BASIC MESHES
	GLfloat triangleVertices[15] =
	{//    COORDINATES           /      UV
		 0.0f,      2.0f, 0.0f,		0.0f,       2.0f,
		 1.7321f,  -1.0f, 0.0f,		1.7321f,   -1.0f,
		-1.7321f,  -1.0f, 0.0f,	   -1.7321f,   -1.0f
	};
	GLsizeiptr triangleVerticesSize = sizeof(triangleVertices);

	GLfloat squareVertices[20] =
	{//    COORDINATES       /      UV
		-0.5f, -0.5f, 0.0f,		0.0f, 0.0f,
		-0.5f,  0.5f, 0.0f,		0.0f, 1.0f,
		 0.5f,  0.5f, 0.0f,		1.0f, 1.0f,
		 0.5f, -0.5f, 0.0f,		1.0f, 0.0f
	};
	GLsizeiptr squareVerticesSize = sizeof(squareVertices);

	GLuint squareIndices[6] =
	{
		0, 1, 2,
		0, 3, 2
	};
	GLsizeiptr squareIndicesSize = sizeof(squareIndices);

	//BASIC SHADERS
	Shader* simpleParticleShaderProgram;

	double deltaTime = 0.0;
	double time = 0.0;

	enum SHADERS
	{
		PARTICLE
	};
private:

	//FPS COUNTER
	double prevTime = 0.0;
	double crntTime = 0.0;


public:
	static void Init(int& WINDOW_WIDTH, int& WINDOW_HEIGHT, const char* TITLE) { return Get().IInit(WINDOW_WIDTH, WINDOW_HEIGHT, TITLE); }
	static void TimeTick() { return Get().ITimeTick(); }


private:
	void IInit(int& WINDOW_WIDTH, int& WINDOW_HEIGHT, const char* TITLE);
	void ITimeTick();

public:
	Engine(const Engine&) = delete;

	static Engine& Get()
	{
		static Engine instance;
		return instance;
	}

private:
	Engine() {}
};

#endif