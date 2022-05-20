#pragma once
#include "Core.h"
#include "Vec3.h"
#include "Shader.h"

#include <glm/glm.hpp>

namespace absGL
{
	enum class SpotLightDistances
	{
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

	struct ABSGL_API SpotLight
	{

	public:

		SpotLight(Vec3 position, Vec3 direction, Vec3 ambient, Vec3 diffuse, Vec3 specular, 
			SpotLightDistances distance, float cutoff, float outerCutoff);

		SpotLight(Vec3 position, Vec3 direction, Vec3 ambient, Vec3 diffuse, Vec3 specular,
			float cutoff, float outerCutoff,
			float constant, float linear, float quadratic);

		~SpotLight();

		void UpdateShader(Shader& shader);

		static unsigned int LightCount;
		unsigned int Index;

		glm::vec3 Position;

		float Constant;
		float Linear;
		float Quadratic;

		glm::vec3 Ambient;
		glm::vec3 Diffuse;
		glm::vec3 Specular;
		glm::vec3 Direction;

		float CutOff;
		float OuterCutOff;
		
	};
}