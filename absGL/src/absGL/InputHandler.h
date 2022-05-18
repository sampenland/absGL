#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "Core.h"

namespace absGL
{
	class ABSGL_API InputHandler
	{

	public:

		InputHandler();
		~InputHandler();

		void ProcessInputs(GLFWwindow* window);
		void Keyboard(GLFWwindow* window);

	public:

		static int s_LastX;
		static int s_LastY;

		static void Mouse(GLFWwindow* window, double xposIn, double yposIn);
		static void MouseScroll(GLFWwindow* window, double xoffset, double yoffset);

	private:


	};
}