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

        inline unsigned int ShadowMapID() const { return m_ShadowMapID; }
        inline glm::mat4 LightSpaceMatrix() const { return m_LightSpaceMatrix; }

        void RenderShadowMap(Light* light);

        ShadowMap(Renderer* render);
        ~ShadowMap();

	private:

        unsigned int m_ShadowWidth, m_ShadowHeight;
        Renderer* m_Render = nullptr;
        unsigned int m_ShadowMapID;
        unsigned int m_DepthMapFBO;
        glm::mat4 m_LightSpaceMatrix;

	};
}