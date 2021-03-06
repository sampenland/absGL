#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "Core.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

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

    private:

        void CheckCompileErrors(unsigned int shader, std::string type);

    };
}

