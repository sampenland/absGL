#include "absGLpch.h"
#include "InputHandler.h"
#include "Renderer.h"

namespace absGL
{
	int InputHandler::s_LastX = 0;
	int InputHandler::s_LastY = 0;

	InputHandler::InputHandler()
	{

	}

	InputHandler::~InputHandler()
	{

	}

	void InputHandler::ProcessInputs(GLFWwindow* window)
	{
		glfwPollEvents();
		Keyboard(window);
	}

	void InputHandler::Keyboard(GLFWwindow* window)
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);

		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			Renderer::s_Camera->ProcessKeyboard(FORWARD, Renderer::s_DeltaTime);
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			Renderer::s_Camera->ProcessKeyboard(BACKWARD, Renderer::s_DeltaTime);
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			Renderer::s_Camera->ProcessKeyboard(LEFT, Renderer::s_DeltaTime);
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			Renderer::s_Camera->ProcessKeyboard(RIGHT, Renderer::s_DeltaTime);
	}

	void InputHandler::MouseScroll(GLFWwindow* window, double xoffset, double yoffset)
	{
		Renderer::s_Camera->ProcessMouseScroll(static_cast<float>(yoffset));
	}

	void InputHandler::Mouse(GLFWwindow* window, double xposIn, double yposIn)
	{
		float xpos = static_cast<float>(xposIn);
		float ypos = static_cast<float>(yposIn);

		static bool firstMouse = true;
		if (firstMouse)
		{
			s_LastX = xpos;
			s_LastY = ypos;
			firstMouse = false;
		}

		float xoffset = xpos - s_LastX;
		float yoffset = s_LastY - ypos; // reversed since y-coordinates go from bottom to top

		s_LastX = xpos;
		s_LastY = ypos;

		Renderer::s_Camera->ProcessMouseMovement(xoffset, yoffset);
	}
}