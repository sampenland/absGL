#pragma once
#include "absGLpch.h"
#include "PointLight.h"
#include "Renderer.h"

namespace absGL
{
	unsigned int PointLight::LightCount = 0;

	PointLight::PointLight(Renderer* renderer, Shader* shader, Vec4 color, Vec3 position, Vec3 ambient, Vec3 diffuse, Vec3 specular, PointLightDistances distance)
		: Constant(1.0f), Linear(0.7f), Quadratic(1.8f), Light(shader, renderer, position.GetGLM())
	{
		Color = glm::vec4(color.X, color.Y, color.Z, color.W);
		Position = glm::vec3(position.X, position.Y, position.Z);
		Ambient = glm::vec3(ambient.X, ambient.Y, ambient.Z);
		Diffuse = glm::vec3(diffuse.X, diffuse.Y, diffuse.Z);
		Specular = glm::vec3(specular.X, specular.Y, specular.Z);

		switch (distance)
		{
		case PointLightDistances::DISTANCE_1:
			Constant = 1.0f;
			Linear = 3.7f;
			Quadratic = 4.8f;
			break;
		case PointLightDistances::DISTANCE_2:
			Constant = 1.0f;
			Linear = 2.7f;
			Quadratic = 3.8f;
			break;
		case PointLightDistances::DISTANCE_5:
			Constant = 1.0f;
			Linear = 1.7f;
			Quadratic = 2.8f;
			break;
		case PointLightDistances::DISTANCE_13:
			Constant = 1.0f;
			Linear = 0.35f;
			Quadratic = 0.44f;
			break;
		case PointLightDistances::DISTANCE_20:
			Constant = 1.0f;
			Linear = 0.22f;
			Quadratic = 0.20f;
			break;
		case PointLightDistances::DISTANCE_32:
			Constant = 1.0f;
			Linear = 0.14f;
			Quadratic = 0.07f;
			break;
		case PointLightDistances::DISTANCE_50:
			Constant = 1.0f;
			Linear = 0.09f;
			Quadratic = 0.032f;
			break;
		case PointLightDistances::DISTANCE_65:
			Constant = 1.0f;
			Linear = 0.07f;
			Quadratic = 0.017f;
			break;
		case PointLightDistances::DISTANCE_100:
			Constant = 1.0f;
			Linear = 0.045f;
			Quadratic = 0.0075f;
			break;
		case PointLightDistances::DISTANCE_160:
			Constant = 1.0f;
			Linear = 0.027f;
			Quadratic = 0.0028f;
			break;
		case PointLightDistances::DISTANCE_200:
			Constant = 1.0f;
			Linear = 0.022f;
			Quadratic = 0.0019f;
			break;
		case PointLightDistances::DISTANCE_325:
			Constant = 1.0f;
			Linear = 0.014f;
			Quadratic = 0.0007f;
			break;
		case PointLightDistances::DISTANCE_600:
			Constant = 1.0f;
			Linear = 0.007f;
			Quadratic = 0.0002f;
			break;
		case PointLightDistances::DISTANCE_3250:
			Constant = 1.0f;
			Linear = 0.0014f;
			Quadratic = 0.000007f;
			break;
		}

		Index = LightCount;
		LightCount++;

	}

	PointLight::PointLight(Renderer* renderer, Shader* shader, Vec4 color, Vec3 position, Vec3 ambient, Vec3 diffuse, Vec3 specular,
		float constant, float linear, float quadratic)
		: Constant(constant), Linear(linear), Quadratic(quadratic), Light(shader, renderer, position.GetGLM())
	{
		Color = glm::vec4(color.X, color.Y, color.Z, color.W);
		Position = glm::vec3(position.X, position.Y, position.Z);
		Ambient = glm::vec3(ambient.X, ambient.Y, ambient.Z);
		Diffuse = glm::vec3(diffuse.X, diffuse.Y, diffuse.Z);
		Specular = glm::vec3(specular.X, specular.Y, specular.Z);

		Index = LightCount;
		LightCount++;
	}

	PointLight::~PointLight()
	{
		LightCount--;
	}

	void PointLight::UpdateShader()
	{
		m_CurrentShader->Use();
		
		m_CurrentShader->SetVec3("viewPos", Renderer::s_Camera->Position);
		m_CurrentShader->SetInt("pointLightCount", LightCount);
		
		m_CurrentShader->SetVec4("pointLights[" + std::to_string(Index) + "].color", Color);
		m_CurrentShader->SetVec3("pointLights[" + std::to_string(Index) + "].position", Position);
		
		m_CurrentShader->SetVec3("pointLights[" + std::to_string(Index) + "].ambient", Ambient);
		m_CurrentShader->SetVec3("pointLights[" + std::to_string(Index) + "].diffuse", Diffuse);
		m_CurrentShader->SetVec3("pointLights[" + std::to_string(Index) + "].specular", Specular);
		
		m_CurrentShader->SetFloat("pointLights[" + std::to_string(Index) + "].constant", Constant);
		m_CurrentShader->SetFloat("pointLights[" + std::to_string(Index) + "].linear", Linear);
		m_CurrentShader->SetFloat("pointLights[" + std::to_string(Index) + "].quadratic", Quadratic);
	}

}