#pragma once

#include "Core.h"
#include "Model.h"
#include "Camera.h"

namespace absGL
{
	class ABSGL_API Renderer
	{
	public:

		static Camera* s_Camera;
		static Vector<Model> s_Models;
		static unsigned int s_Width;
		static unsigned int s_Height;
		static float s_DeltaTime;
		static float s_LastFrame;

	private:

		GLFWwindow* m_Window = nullptr;

	public:

		Renderer(const std::string& title, unsigned int width, unsigned int height);
		~Renderer();

		static inline void AddModel(Model& model) { s_Models.Push(model); }
		
		inline void HideMouse(bool val) { glfwSetInputMode(m_Window, GLFW_CURSOR, val ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL); }
		inline GLFWwindow* GetWindow() const { return m_Window; }

		void StartRender();
		void Render();
		void EndRender();

		bool ShouldClose();

	};
}

