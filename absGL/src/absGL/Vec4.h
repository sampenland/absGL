#pragma once

#include "Core.h"

namespace absGL
{
	struct ABSGL_API Vec4
	{
		float X;
		float Y;
		float Z;
		float W;

		Vec4(float x, float y, float z, float w)
			: X(x), Y(y), Z(z), W(w)
		{

		}
	};
}