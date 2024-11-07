#include"engine.h"

void Engine::IInit(int& WINDOW_WIDTH, int& WINDOW_HEIGHT, const char* title)
{
	// INIT GLFW
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	Logger::log(INFO, "GLFW initialized");


	//INIT WINDOW
	Engine::window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, title, NULL, NULL);
	if (Engine::window == NULL)
	{
		std::cout << "Failed to create a GLFW window!" << std::endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(Engine::window);
	Logger::log(INFO, "Window initialized");

	//INIT OPENGL
	gladLoadGL();
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	Logger::log(INFO, "OpenGL initialized");
}

void Engine::ITimeTick()
{
	Engine::crntTime = glfwGetTime();
	Engine::deltaTime = crntTime - prevTime;
	Engine::prevTime = Engine::crntTime;
	Engine::time += Engine::deltaTime;
}