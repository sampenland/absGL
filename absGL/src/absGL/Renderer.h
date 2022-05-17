#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "Core.h"
#include "Model.h"

#include <vector>
#include <string>

namespace absGL
{
	class ABSGL_API Renderer
	{

	private:

		GLFWwindow* m_Window = nullptr;
		std::vector<Model*> m_Models;

	public:

		Renderer(const std::string& title, unsigned int width, unsigned int height);
		~Renderer();

		inline GLFWwindow* GetWindow() const { return m_Window; }

		void StartRender();
		void Render();
		void EndRender();

		bool ShouldClose();

	};
}

