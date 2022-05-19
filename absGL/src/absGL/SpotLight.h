#pragma once
#include "Core.h"
#include "Vec3.h"

#include <glm/glm.hpp>

namespace absGL
{
	class ABSGL_API PointLight
	{

	public:

		PointLight(Vec3 position, Vec3 direction, Vec3 ambient, Vec3 diffuse, Vec3 specular)
		{
			m_Position = glm::vec3(position.X, position.Y, position.Z);
			m_Direction = glm::vec3(direction.X, direction.Y, direction.Z);
			m_Ambient = glm::vec3(ambient.X, ambient.Y, ambient.Z);
			m_Diffuse = glm::vec3(diffuse.X, diffuse.Y, diffuse.Z);
			m_Specular = glm::vec3(specular.X, specular.Y, specular.Z);
		}

	private:

		glm::vec3 m_Position;

		float constant;
		float linear;
		float quadratic;

		glm::vec3 m_Ambient;
		glm::vec3 m_Diffuse;
		glm::vec3 m_Specular;
		glm::vec3 m_Direction;

		float cutOff;
		float outerCutOff;
	};
}