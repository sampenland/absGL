#pragma once
#include "Core.h"
#include "Vec3.h"
#include "Vec4.h"
#include "Shader.h"
#include "Light.h"

#include <glm/glm.hpp>

namespace absGL
{
	enum class PointLightDistances
	{
		DISTANCE_1,
		DISTANCE_2,
		DISTANCE_5,
		DISTANCE_7,
		DISTANCE_13,	
		DISTANCE_20,
		DISTANCE_32,
		DISTANCE_50,
		DISTANCE_65,
		DISTANCE_100,
		DISTANCE_160,
		DISTANCE_200,
		DISTANCE_325,
		DISTANCE_600,
		DISTANCE_3250
	};

	struct ABSGL_API PointLight
		: Light
	{

	public:

		PointLight(Vec4 color, Vec3 position, Shader* shader, Vec3 ambient, Vec3 diffuse, Vec3 specular, PointLightDistances distance);

		PointLight(Vec4 color, Vec3 position, Shader* shader, Vec3 ambient, Vec3 diffuse, Vec3 specular,
			float constant = 1.0f, float linear = 0.7f, float quadratic = 1.8f);

		~PointLight();

		void UpdateShader();

		static unsigned int LightCount;

		unsigned int Index;

		glm::vec3 Position;
		glm::vec3 Ambient;
		glm::vec3 Diffuse;
		glm::vec3 Specular;
		glm::vec4 Color;

		float Constant;
		float Linear;
		float Quadratic;

	};
}