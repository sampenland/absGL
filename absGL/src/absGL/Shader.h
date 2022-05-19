#pragma once
#include "Core.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "glm/gtc/type_ptr.hpp"

#include <string>
#include <unordered_map>

namespace absGL
{
    class ABSGL_API Shader
    {

    public:

        unsigned int m_RenderID;

        Shader(const char* vertexPath, const char* fragmentPath);

        void Use();

        void SetBool(const std::string& name, bool value) const;

        void SetInt(const std::string& name, int value) const;

        void SetFloat(const std::string& name, float value) const;

        void SetMat4(const std::string& name, glm::mat4 value) const;

    private:

        GLint GetUniformLocation(const std::string& name) const;
        void CheckCompileErrors(unsigned int shader, std::string type);

        mutable std::unordered_map<std::string, GLint> m_Uniforms;

    };
}

