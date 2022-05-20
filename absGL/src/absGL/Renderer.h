#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "Core.h"
#include "Model.h"
#include "Camera.h"
#include "Shader.h"
#include "Light.h"

#include <vector>

namespace absGL
{
	class ABSGL_API Renderer
	{
	public:

		static Camera* s_Camera;
		static std::vector<Model*> s_Models;
		static std::vector<Light*> s_Lights;
		static unsigned int s_Width;
		static unsigned int s_Height;
		static float s_DeltaTime;
		static float s_LastFrame;
		
	public:

		void SetCameraPosition(float x, float y, float z);

		static inline void AddModel(Model* model) { s_Models.push_back(model); }
		static inline void AddLight(Light* light) { s_Lights.push_back(light); }
		
		inline void HideMouse(bool val) { glfwSetInputMode(m_Window, GLFW_CURSOR, val ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL); }
		inline GLFWwindow* GetWindow() const { return m_Window; }

		Renderer(const std::string& title, unsigned int width, unsigned int height);
		void SetShadowMapShader(Shader* shadowShader);
		~Renderer();

		void StartRender();
		void ShadowMapRender(Light& light);
		void RenderModels();
		void RenderLights();
		void Render();
		void EndRender();

		bool ShouldClose();

	private:

		GLFWwindow* m_Window = nullptr;
		Shader* m_ShadowShader = nullptr;

		const unsigned int SHADOW_WIDTH = 1024;
		const unsigned int SHADOW_HEIGHT = 1024;

	};
}

