#pragma once

#include "Core.h"

namespace absGL
{
	struct ABSGL_API Material
	{
		Material(float shininess = 32)
			: Shininess(shininess)
		{

		}

		float Shininess;

	};
}