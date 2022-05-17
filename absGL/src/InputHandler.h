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

	private:

	};
}