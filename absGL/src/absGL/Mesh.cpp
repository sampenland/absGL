#include "Mesh.h"

namespace absGL
{
	Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
	{
        this->m_Vertices = vertices;
        this->m_Indices = indices;
        this->m_Textures = textures;

        SetupMesh();

	}

	void Mesh::Render(Shader& shader)
	{
        unsigned int diffuseNr = 1;
        unsigned int specularNr = 1;
        for (unsigned int i = 0; i < m_Textures.size(); i++)
        {
            glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding
            // retrieve texture number (the N in diffuse_textureN)
            std::string number;
            std::string name = m_Textures[i].Type;
            if (name == "texture_diffuse")
                number = std::to_string(diffuseNr++);
            else if (name == "texture_specular")
                number = std::to_string(specularNr++);

            shader.SetFloat(("material." + name + number).c_str(), i);
            glBindTexture(GL_TEXTURE_2D, m_Textures[i].m_RenderID);
        }
        glActiveTexture(GL_TEXTURE0);

        // draw mesh
        glBindVertexArray(m_VAORenderID);
        glDrawElements(GL_TRIANGLES, m_Indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
	}

	void Mesh::SetupMesh()
	{
        glGenVertexArrays(1, &m_VAORenderID);
        glGenBuffers(1, &m_VBORenderID);
        glGenBuffers(1, &m_EBORenderID);

        glBindVertexArray(m_VAORenderID);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBORenderID);

        glBufferData(GL_ARRAY_BUFFER, m_Vertices.size() * sizeof(Vertex), &m_Vertices[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBORenderID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Indices.size() * sizeof(unsigned int),
            &m_Indices[0], GL_STATIC_DRAW);

        // vertex positions
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
        // vertex normals
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
        // vertex texture coords
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

        glBindVertexArray(0);
	}
}