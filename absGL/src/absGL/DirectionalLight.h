#pragma once
#include "Core.h"
#include "Vec3.h"
#include "Vec4.h"
#include "Shader.h"
#include "Light.h"

#include <glm/glm.hpp>

namespace absGL
{
	struct ABSGL_API DirectionalLight
		: public Light
	{

	public:

		DirectionalLight(Renderer* renderer, Shader* shader, Vec4 color, Vec3 direction, Vec3 ambient, Vec3 diffuse, Vec3 specular);
		~DirectionalLight();

		void UpdateShader() override;

		static unsigned int LightCount;

		unsigned int Index;

		glm::vec3 Direction;
		glm::vec3 Ambient;
		glm::vec3 Diffuse;
		glm::vec3 Specular;
		glm::vec4 Color;
		
	};
}