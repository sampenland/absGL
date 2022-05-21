#pragma once

#include "Core.h"
#include "Shader.h"
#include "ShadowMap.h"

namespace absGL
{
	struct ABSGL_API Light
	{

	public:

		virtual void UpdateShader() = 0;

		Light(Shader* shader, Renderer* renderer, glm::vec3 position);
		~Light();

		void RenderShadowMap();

		static unsigned int LightCount;
		glm::vec3 Position;

	protected:

		Shader* m_CurrentShader = nullptr;
		ShadowMap* m_ShadowMap = nullptr;

	};
}