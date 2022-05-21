#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "Core.h"
#include "Shader.h"
#include "Renderer.h"

namespace absGL
{
    class Light;

	class ABSGL_API ShadowMap
	{

	public:

        void RenderShadowMap(Light* light);

        ShadowMap(Renderer* render);
        ~ShadowMap();

	private:

        unsigned int m_ShadowWidth, m_ShadowHeight;
        Renderer* m_Render = nullptr;
        unsigned int m_ShadowMapID;
        unsigned int m_DepthMapFBO;

	};
}