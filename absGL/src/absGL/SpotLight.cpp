#include "absGLpch.h"
#include "SpotLight.h"
#include "Renderer.h"

namespace absGL
{
	unsigned int SpotLight::LightCount = 0;

	SpotLight::SpotLight(Vec3 position, Vec3 direction, Vec3 ambient, Vec3 diffuse, Vec3 specular,
		SpotLightDistances distance, float cutoff, float outerCutoff)
		: Constant(1.0f), Linear(0.7f), Quadratic(1.8f)
	{
		Direction = glm::vec3(direction.X, direction.Y, direction.Z);
		Position = glm::vec3(position.X, position.Y, position.Z);
		Ambient = glm::vec3(ambient.X, ambient.Y, ambient.Z);
		Diffuse = glm::vec3(diffuse.X, diffuse.Y, diffuse.Z);
		Specular = glm::vec3(specular.X, specular.Y, specular.Z);

		switch (distance)
		{
		case SpotLightDistances::DISTANCE_7:
			Constant = 1.0f;
			Linear = 0.7f;
			Quadratic = 1.8f;
			break;
		case SpotLightDistances::DISTANCE_13:
			Constant = 1.0f;
			Linear = 0.35f;
			Quadratic = 0.44f;
			break;
		case SpotLightDistances::DISTANCE_20:
			Constant = 1.0f;
			Linear = 0.22f;
			Quadratic = 0.20f;
			break;
		case SpotLightDistances::DISTANCE_32:
			Constant = 1.0f;
			Linear = 0.14f;
			Quadratic = 0.07f;
			break;
		case SpotLightDistances::DISTANCE_50:
			Constant = 1.0f;
			Linear = 0.09f;
			Quadratic = 0.032f;
			break;
		case SpotLightDistances::DISTANCE_65:
			Constant = 1.0f;
			Linear = 0.07f;
			Quadratic = 0.017f;
			break;
		case SpotLightDistances::DISTANCE_100:
			Constant = 1.0f;
			Linear = 0.045f;
			Quadratic = 0.0075f;
			break;
		case SpotLightDistances::DISTANCE_160:
			Constant = 1.0f;
			Linear = 0.027f;
			Quadratic = 0.0028f;
			break;
		case SpotLightDistances::DISTANCE_200:
			Constant = 1.0f;
			Linear = 0.022f;
			Quadratic = 0.0019f;
			break;
		case SpotLightDistances::DISTANCE_325:
			Constant = 1.0f;
			Linear = 0.014f;
			Quadratic = 0.0007f;
			break;
		case SpotLightDistances::DISTANCE_600:
			Constant = 1.0f;
			Linear = 0.007f;
			Quadratic = 0.0002f;
			break;
		case SpotLightDistances::DISTANCE_3250:
			Constant = 1.0f;
			Linear = 0.0014f;
			Quadratic = 0.000007f;
			break;
		}

		CutOff = cutoff;
		OuterCutOff = outerCutoff;

		Index = LightCount;
		LightCount++;

	}

	SpotLight::SpotLight(Vec3 position, Vec3 direction, Vec3 ambient, Vec3 diffuse, Vec3 specular,
		float cutoff, float outerCutoff,
		float constant, float linear, float quadratic)
		: Constant(constant), Linear(linear), Quadratic(quadratic), 
		CutOff(cutoff), OuterCutOff(outerCutoff)
	{
		Direction = glm::vec3(direction.X, direction.Y, direction.Z);
		Position = glm::vec3(position.X, position.Y, position.Z);
		Ambient = glm::vec3(ambient.X, ambient.Y, ambient.Z);
		Diffuse = glm::vec3(diffuse.X, diffuse.Y, diffuse.Z);
		Specular = glm::vec3(specular.X, specular.Y, specular.Z);

		Index = LightCount;
		LightCount++;
	}

	SpotLight::~SpotLight()
	{
		LightCount--;
	}

	void SpotLight::UpdateShader(Shader& shader)
	{
		shader.Use();

		shader.SetVec3("viewPos", Renderer::s_Camera->Position);
		shader.SetInt("spotLightCount", LightCount);

		shader.SetVec3("spotLights[" + std::to_string(Index) + "].position", Position);
		shader.SetVec3("spotLights[" + std::to_string(Index) + "].direction", Direction);

		shader.SetVec3("spotLights[" + std::to_string(Index) + "].ambient", Ambient);
		shader.SetVec3("spotLights[" + std::to_string(Index) + "].diffuse", Diffuse);
		shader.SetVec3("spotLights[" + std::to_string(Index) + "].specular", Specular);

		shader.SetFloat("spotLights[" + std::to_string(Index) + "].constant", Constant);
		shader.SetFloat("spotLights[" + std::to_string(Index) + "].linear", Linear);
		shader.SetFloat("spotLights[" + std::to_string(Index) + "].quadratic", Quadratic);

		shader.SetFloat("spotLights[" + std::to_string(Index) + "].cutOff", CutOff);
		shader.SetFloat("spotLights[" + std::to_string(Index) + "].outerCutOff", OuterCutOff);
	}
}