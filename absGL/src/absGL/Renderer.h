#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "Core.h"
#include "Model.h"
#include "Camera.h"
#include "Vector.h"

#include <string>

namespace absGL
{
	class ABSGL_API Renderer
	{
	public:

		static Camera* s_Camera;
		static Vector<Model> s_Models;

	private:

		GLFWwindow* m_Window = nullptr;

	public:

		Renderer(const std::string& title, unsigned int width, unsigned int height);
		~Renderer();

		static inline void AddModel(Model& model) { s_Models.Push(model); }

		inline GLFWwindow* GetWindow() const { return m_Window; }

		void StartRender();
		void Render();
		void EndRender();

		bool ShouldClose();

	};
}

