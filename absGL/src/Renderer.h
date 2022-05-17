#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "Core.h"
#include "Model.h"

#include <vector>

namespace absGL
{
	class ABSGL_API Renderer
	{

	private:

		GLFWwindow* m_Window = nullptr;
		std::vector<Model*> m_Models;

		const unsigned int SCR_WIDTH = 800;
		const unsigned int SCR_HEIGHT = 600;

	public:

		Renderer();
		~Renderer();

		inline GLFWwindow* GetWindow() const { return m_Window; }

		void StartRender();
		void Render();
		void EndRender();

	};
}

