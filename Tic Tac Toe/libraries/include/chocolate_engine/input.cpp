#include"Input.h"

bool Input::IGetKeyDown(int key)
{
	if (glfwGetKey(Engine::Get().window, key) == GLFW_PRESS)
	{
		return true;
	}
	else
	{
		false;
	}
}