#include "absGLpch.h"
#include "Renderer.h"
#include "InputHandler.h"
#include "Light.h"

#include <iostream>

namespace absGL
{
	Camera* Renderer::s_Camera = nullptr;
	Shader* Renderer::s_ShadowShader = nullptr;
	std::vector<Model*> Renderer::s_Models;
	std::vector<Light*> Renderer::s_Lights;
	unsigned int Renderer::s_Width = 800;
	unsigned int Renderer::s_Height = 600;
	float Renderer::s_DeltaTime = 0.f;
	float Renderer::s_LastFrame = 0.f;

	void framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}

	void APIENTRY error_callback(
		GLenum source,
		GLenum type,
		unsigned int id,
		GLenum severity,
		GLsizei length,
		const char* message,
		const void* userParam)
	{
		// ignore non-significant error/warning codes
		if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

		std::cout << "---------------" << std::endl;
		std::cout << "Debug message (" << id << "): " << message << std::endl;

		switch (source)
		{
		case GL_DEBUG_SOURCE_API:             std::cout << "Source: API"; break;
		case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   std::cout << "Source: Window System"; break;
		case GL_DEBUG_SOURCE_SHADER_COMPILER: std::cout << "Source: Shader Compiler"; break;
		case GL_DEBUG_SOURCE_THIRD_PARTY:     std::cout << "Source: Third Party"; break;
		case GL_DEBUG_SOURCE_APPLICATION:     std::cout << "Source: Application"; break;
		case GL_DEBUG_SOURCE_OTHER:           std::cout << "Source: Other"; break;
		} std::cout << std::endl;

		switch (type)
		{
		case GL_DEBUG_TYPE_ERROR:               std::cout << "Type: Error"; break;
		case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: std::cout << "Type: Deprecated Behaviour"; break;
		case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  std::cout << "Type: Undefined Behaviour"; break;
		case GL_DEBUG_TYPE_PORTABILITY:         std::cout << "Type: Portability"; break;
		case GL_DEBUG_TYPE_PERFORMANCE:         std::cout << "Type: Performance"; break;
		case GL_DEBUG_TYPE_MARKER:              std::cout << "Type: Marker"; break;
		case GL_DEBUG_TYPE_PUSH_GROUP:          std::cout << "Type: Push Group"; break;
		case GL_DEBUG_TYPE_POP_GROUP:           std::cout << "Type: Pop Group"; break;
		case GL_DEBUG_TYPE_OTHER:               std::cout << "Type: Other"; break;
		} std::cout << std::endl;

		switch (severity)
		{
		case GL_DEBUG_SEVERITY_HIGH:         std::cout << "Severity: high"; break;
		case GL_DEBUG_SEVERITY_MEDIUM:       std::cout << "Severity: medium"; break;
		case GL_DEBUG_SEVERITY_LOW:          std::cout << "Severity: low"; break;
		case GL_DEBUG_SEVERITY_NOTIFICATION: std::cout << "Severity: notification"; break;
		} std::cout << std::endl;
		std::cout << std::endl;
	}

	Renderer::Renderer(const std::string& title, unsigned int width, unsigned int height)
	{
		s_Width = width;
		s_Height = height;

		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);

		m_Window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
		if (m_Window == NULL)
		{
			std::cout << "Failed to create GLFW window" << std::endl;
			glfwTerminate();
			return;
		}
		glfwMakeContextCurrent(m_Window);
		glfwSetFramebufferSizeCallback(m_Window, framebuffer_size_callback);
		glfwSetCursorPosCallback(m_Window, InputHandler::Mouse);
		glfwSetScrollCallback(m_Window, InputHandler::MouseScroll);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
			return;
		}

		int flags; 
		glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
		if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
		{
			glEnable(GL_DEBUG_OUTPUT);
			glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
			glDebugMessageCallback(error_callback, nullptr);
			glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
		}

		glDebugMessageControl(GL_DEBUG_SOURCE_API,
			GL_DEBUG_TYPE_ERROR,
			GL_DEBUG_SEVERITY_HIGH,
			0, nullptr, GL_TRUE);

		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glEnable(GL_DEPTH_TEST);

		s_Camera = new Camera();

		std::cout << "Renderer Created" << std::endl;
	}

	Renderer::~Renderer()
	{
		glfwTerminate();
	}

	void Renderer::StartRender()
	{
		float currentFrame = static_cast<float>(glfwGetTime());
		s_DeltaTime = currentFrame - s_LastFrame;
		s_LastFrame = currentFrame;

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Renderer::RenderLights()
	{
		/*for (int i = 0; i < s_Lights.size(); i++)
		{
			Light& light = *s_Lights[i];
			light.RenderShadowMap();
		}*/

		// reset viewport
		glViewport(0, 0, s_Width, s_Height);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		for (int i = 0; i < s_Lights.size(); i++)
		{
			Light& light = *s_Lights[i];
			light.UpdateShader();
		}
	}

	void Renderer::RenderModels()
	{
		for (int i = 0; i < s_Models.size(); i++)
		{
			Model& model = *s_Models[i];
			model.Render();
		}
	}

	void Renderer::RenderModels(Shader* shader)
	{
		for (int i = 0; i < s_Models.size(); i++)
		{
			Model& model = *s_Models[i];
			model.Render(shader);
		}
	}

	void Renderer::Render()
	{
		RenderLights();
		RenderModels();
	}

	void Renderer::EndRender()
	{
		glfwSwapBuffers(m_Window);
	}

	bool Renderer::ShouldClose()
	{
		return glfwWindowShouldClose(m_Window);
	}

	void Renderer::SetCameraPosition(float x, float y, float z)
	{
		s_Camera->Position = glm::vec3(x, y, z);
	}
}