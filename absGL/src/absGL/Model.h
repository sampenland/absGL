#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "Core.h"
#include "Shader.h"

namespace absGL
{

	class ABSGL_API Model
	{

	public:

		Model(float* vertices, unsigned int* indices);
		~Model();

		void Render(Shader* shader);

	private:

		unsigned int m_VAORenderID;
		unsigned int m_VBORenderID;
		unsigned int m_EBORenderID;

	};

}


