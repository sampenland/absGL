#pragma once

#include "Core.h"

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
			: Type(type), CurrentShader(shader)
		{

		};

		LightTypes Type;

	protected:

		Shader* CurrentShader;

	};
}