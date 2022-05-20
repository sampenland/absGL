#include "absGLpch.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "Shader.h"

namespace absGL
{
    Shader::Shader(const char* vertexPath, const char* fragmentPath)
    {
        // 1. retrieve the vertex/fragment source code from filePath
        std::string vertexCode;
        std::string fragmentCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;
        // ensure ifstream objects can throw exceptions:
        vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try
        {
            // open files
            vShaderFile.open(vertexPath);
            fShaderFile.open(fragmentPath);
            std::stringstream vShaderStream, fShaderStream;
            // read file's buffer contents into streams
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();
            // close file handlers
            vShaderFile.close();
            fShaderFile.close();
            // convert stream into string
            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();
        }
        catch (std::ifstream::failure& e)
        {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: " << e.what() << std::endl;
        }
        const char* vShaderCode = vertexCode.c_str();
        const char* fShaderCode = fragmentCode.c_str();
        // 2. compile shaders
        unsigned int vertex, fragment;
        // vertex shader
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);
        CheckCompileErrors(vertex, "VERTEX");
        // fragment Shader
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);
        CheckCompileErrors(fragment, "FRAGMENT");
        // shader Program
        m_RenderID = glCreateProgram();
        glAttachShader(m_RenderID, vertex);
        glAttachShader(m_RenderID, fragment);
        glLinkProgram(m_RenderID);
        CheckCompileErrors(m_RenderID, "PROGRAM");
        // delete the shaders as they're linked into our program now and no longer necessary
        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }

    void Shader::Use()
    {
        glUseProgram(m_RenderID);
    }

    void Shader::Release()
    {
        glUseProgram(0);
    }

    void Shader::SetBool(const std::string& name, bool value) const
    {
        GLint loc = GetUniformLocation(name);
        glUniform1i(loc, (int)value);
    }

    void Shader::SetInt(const std::string& name, int value) const
    {
        GLint loc = GetUniformLocation(name);
        glUniform1i(loc, value);
    }

    void Shader::SetFloat(const std::string& name, float value) const
    {
        GLint loc = GetUniformLocation(name);
        glUniform1f(loc, value);
    }

    void Shader::SetVec3(const std::string& name, const glm::vec3& value) const
    {
        GLint loc = GetUniformLocation(name);
        glUniform3fv(loc, 1, &value[0]);
    }

    void Shader::SetVec3(const std::string& name, float x, float y, float z) const
    {
        GLint loc = GetUniformLocation(name);
        glUniform3f(loc, x, y, z);
    }
    
    void Shader::SetVec4(const std::string& name, const glm::vec4& value) const
    {
        GLint loc = GetUniformLocation(name);
        glUniform3fv(loc, 1, &value[0]);
    }

    void Shader::SetVec4(const std::string& name, float x, float y, float z, float w) const
    {
        GLint loc = GetUniformLocation(name);
        glUniform3f(loc, x, y, z);
    }
    

    void Shader::SetMat4(const std::string& name, glm::mat4 value) const
    {
        GLint loc = GetUniformLocation(name);
        glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(value));
    }

    GLint Shader::GetUniformLocation(const std::string& name) const
    {
        if (m_Uniforms.find(name) != m_Uniforms.end())
            return m_Uniforms[name];

        m_Uniforms[name] = glGetUniformLocation(m_RenderID, name.c_str());
        return m_Uniforms[name];
    }

    void Shader::CheckCompileErrors(unsigned int shader, std::string type)
    {
        int success;
        char infoLog[1024];
        if (type != "PROGRAM")
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
        else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
    }
}

