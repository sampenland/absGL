#include "InputHandler.h"

namespace absGL
{
	InputHandler::InputHandler()
	{

	}

	InputHandler::~InputHandler()
	{

	}

	void InputHandler::ProcessInputs(GLFWwindow* window)
	{
		glfwPollEvents();

		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);
	}
}