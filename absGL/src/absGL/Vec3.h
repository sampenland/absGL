#pragma once

#include "Core.h"

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
	};
}