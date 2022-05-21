#include "absGLpch.h"
#include "ShadowMap.h"

#include "Light.h"
#include <glm/glm.hpp>

namespace absGL
{
    ShadowMap::ShadowMap(Renderer* render)
        : m_ShadowMapID(0), m_DepthMapFBO(0), m_ShadowWidth(1024), m_ShadowHeight(1024),
        m_Render(render)
    {
        glGenFramebuffers(1, &m_DepthMapFBO);
        glGenTextures(1, &m_ShadowMapID);

        glBindTexture(GL_TEXTURE_2D, m_ShadowMapID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, m_ShadowWidth, m_ShadowHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        float borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
        glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

        // attach depth texture as FBO's depth buffer
        glBindFramebuffer(GL_FRAMEBUFFER, m_DepthMapFBO);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_ShadowMapID, 0);
        glDrawBuffer(GL_NONE);
        glReadBuffer(GL_NONE);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    ShadowMap::~ShadowMap() {};

    void ShadowMap::RenderShadowMap(Light* light)
    {
        glm::mat4 lightProjection, lightView;
        glm::mat4 lightSpaceMatrix;
        float near_plane = 1.0f, far_plane = 7.5f;

        lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
        lightView = glm::lookAt(light->Position, glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
        lightSpaceMatrix = lightProjection * lightView;

        // render scene from light's point of view
        Renderer::s_ShadowShader->Use();
        Renderer::s_ShadowShader->SetMat4("lightSpaceMatrix", lightSpaceMatrix);

        glViewport(0, 0, m_ShadowWidth, m_ShadowHeight);
        glBindFramebuffer(GL_FRAMEBUFFER, m_DepthMapFBO);
        glClear(GL_DEPTH_BUFFER_BIT);

        m_Render->RenderModels(Renderer::s_ShadowShader);

        glBindFramebuffer(GL_FRAMEBUFFER, 0);

    }
}