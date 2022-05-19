#pragma once

#include "Core.h"
#include "Model.h"
#include "Camera.h"

#include <vector>

namespace absGL
{
	class ABSGL_API Renderer
	{
	public:

		static Camera* s_Camera;
		static std::vector<Model*> s_Models;
		static unsigned int s_Width;
		static unsigned int s_Height;
		static float s_DeltaTime;
		static float s_LastFrame;

	private:

		GLFWwindow* m_Window = nullptr;

	public:

		void SetCameraPosition(float x, float y, float z);
		static inline void AddModel(Model* model) { s_Models.push_back(model); }
		
		inline void HideMouse(bool val) { glfwSetInputMode(m_Window, GLFW_CURSOR, val ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL); }
		inline GLFWwindow* GetWindow() const { return m_Window; }

		Renderer(const std::string& title, unsigned int width, unsigned int height);
		~Renderer();

		void StartRender();
		void Render();
		void EndRender();

		bool ShouldClose();

	};
}

