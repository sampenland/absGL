#include "absGLpch.h"
#include "DirectionalLight.h"
#include "Renderer.h"

namespace absGL
{
	unsigned int DirectionalLight::LightCount = 0;

	DirectionalLight::DirectionalLight(Renderer* renderer, Shader* shader, Vec4 color, Vec3 direction, Vec3 ambient, Vec3 diffuse, Vec3 specular)
		: Light(shader, renderer, glm::vec3(1.f))
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

	void DirectionalLight::UpdateShader()
	{
		m_CurrentShader->Use();

		m_CurrentShader->SetVec3("viewPos", Renderer::s_Camera->Position);
		m_CurrentShader->SetInt("directionalLightCount", LightCount);

		m_CurrentShader->SetMat4("lightSpaceMatrix", m_ShadowMap->LightSpaceMatrix());

		m_CurrentShader->SetVec4("directionalLights[" + std::to_string(Index) + "].color", Color);
		
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_ShadowMap->ShadowMapID());
		m_CurrentShader->SetInt("directionalLights[" + std::to_string(Index) + "].shadowMap", 0);

		m_CurrentShader->SetVec3("directionalLights[" + std::to_string(Index) + "].direction", Direction);
		m_CurrentShader->SetVec3("directionalLights[" + std::to_string(Index) + "].ambient", Ambient);
		m_CurrentShader->SetVec3("directionalLights[" + std::to_string(Index) + "].diffuse", Diffuse);
		m_CurrentShader->SetVec3("directionalLights[" + std::to_string(Index) + "].specular", Specular);
		m_CurrentShader->SetInt("directionalLights[" + std::to_string(Index) + "].index", Index);

	}

}