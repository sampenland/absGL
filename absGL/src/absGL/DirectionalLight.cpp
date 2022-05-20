#include "absGLpch.h"
#include "DirectionalLight.h"
#include "Renderer.h"

namespace absGL
{
	unsigned int DirectionalLight::LightCount = 0;

	DirectionalLight::DirectionalLight(Vec4 color, Vec3 direction, Vec3 ambient, Vec3 diffuse, Vec3 specular)
	{
		Color = glm::vec4(color.X, color.Y, color.Z, color.W);
		Direction = glm::vec3(direction.X, direction.Y, direction.Z);
		Ambient = glm::vec3(ambient.X, ambient.Y, ambient.Z);
		Diffuse = glm::vec3(diffuse.X, diffuse.Y, diffuse.Z);
		Specular = glm::vec3(specular.X, specular.Y, specular.Z);

		Index = LightCount;
		LightCount++;
	}	

	DirectionalLight::~DirectionalLight()
	{
		LightCount--;
	}

	void DirectionalLight::UpdateShader(Shader& shader)
	{
		shader.Use();

		shader.SetVec3("viewPos", Renderer::s_Camera->Position);
		shader.SetInt("directionalLightCount", LightCount);

		shader.SetVec4("directionalLights[" + std::to_string(Index) + "].color", Color);

		shader.SetVec3("directionalLights[" + std::to_string(Index) + "].direction", Direction);
		shader.SetVec3("directionalLights[" + std::to_string(Index) + "].ambient", Ambient);
		shader.SetVec3("directionalLights[" + std::to_string(Index) + "].diffuse", Diffuse);
		shader.SetVec3("directionalLights[" + std::to_string(Index) + "].specular", Specular);

	}

}