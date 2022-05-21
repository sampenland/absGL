#pragma once

#include "Core.h"

#include <glm/glm.hpp>

namespace absGL
{
	struct ABSGL_API Vec3
	{
		float X;
		float Y;
		float Z;

		Vec3(float x, float y, float z)
			: X(x), Y(y), Z(z)
		{

		}

		glm::vec3 GetGLM()
		{
			return glm::vec3(X, Y, Z);
		}
	};
}