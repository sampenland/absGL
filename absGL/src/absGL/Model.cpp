#include "Model.h"

#include <iostream>
namespace absGL
{

	Model::Model(const std::string& modelPath)
	{            
        float vertices[] = {
         0.5f,  0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f 
        };

        unsigned int indices[] = {
            0, 1, 3,
            1, 2, 3 
        };

        // Generate buffers
        glGenVertexArrays(1, &m_VAORenderID);
        glGenBuffers(1, &m_VBORenderID);
        glGenBuffers(1, &m_EBORenderID);

        // Bind array buffer
        glBindVertexArray(m_VAORenderID);

        // Bind and add data
        glBindBuffer(GL_ARRAY_BUFFER, m_VBORenderID);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // Indices
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBORenderID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        // Formatting
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // Unbind buffers
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

	}

	Model::~Model()
	{

	}

	void Model::Render(Shader* shader)
	{
        shader->Use();
        glBindVertexArray(m_VAORenderID);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

	}
}