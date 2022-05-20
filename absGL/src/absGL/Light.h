#pragma once

#include "Core.h"
#include <glm/glm.hpp>

namespace absGL
{
	enum class LightTypes
	{
		DIRECTIONAL,
		POINT,
		SPOT
	};

	struct ABSGL_API Light
	{

	public:

		Light(LightTypes type, Shader* shader)
			: Type(type), CurrentShader(shader), 
			Position(glm::vec3(0, 0, 0)), 
			LightSpaceMatrix(glm::mat4(1.f))
		{
		};

		void SetSpaceMatrix(glm::mat4 matrix)
		{
			LightSpaceMatrix = matrix;
		}

		LightTypes Type;
		glm::vec3 Position;
		glm::mat4 LightSpaceMatrix;

	protected:

		Shader* CurrentShader;

	};
}