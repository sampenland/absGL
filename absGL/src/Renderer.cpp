#include "Renderer.h"

#include <iostream>

namespace absGL
{
	void framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}

	Renderer::Renderer(const std::string& title, unsigned int width, unsigned int height)
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		m_Window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
		if (m_Window == NULL)
		{
			std::cout << "Failed to create GLFW window" << std::endl;
			glfwTerminate();
			return;
		}
		glfwMakeContextCurrent(m_Window);
		glfwSetFramebufferSizeCallback(m_Window, framebuffer_size_callback);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
			return;
		}

		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	}

	Renderer::~Renderer()
	{
		glfwTerminate();
	}

	void Renderer::StartRender()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Renderer::Render()
	{
		for (auto model : m_Models)
		{
			model->Render();
		}
	}

	void Renderer::EndRender()
	{
		glfwSwapBuffers(m_Window);
	}

	bool Renderer::ShouldClose()
	{
		return glfwWindowShouldClose(m_Window);
	}
}