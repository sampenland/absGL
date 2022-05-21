#include "absGLpch.h"
#include "Light.h"
#include "Renderer.h"

namespace absGL
{
	unsigned int Light::LightCount = 0;

	Light::Light(Shader* shader, Renderer* renderer, glm::vec3 position)
		: m_CurrentShader(shader), Position(position)
	{
		m_ShadowMap = new ShadowMap(renderer);
		Renderer::AddLight(this);
	}

	void Light::RenderShadowMap()
	{
		if (!m_ShadowMap)
		{
			std::cout << "Cannot render shadow map" << std::endl;
			assert(m_ShadowMap);
			return;
		}

		m_ShadowMap->RenderShadowMap(this);
	}

	Light::~Light()
	{

	}
}