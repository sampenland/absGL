#pragma once

#include "Shader.h"
#include <vector>

#define MAX_BONE_INFLUENCE 4

namespace absGL
{
    struct Vertex {
        // position
        glm::vec3 Position;
        // normal
        glm::vec3 Normal;
        // texCoords
        glm::vec2 TexCoords;
        // tangent
        glm::vec3 Tangent;
        // bitangent
        glm::vec3 Bitangent;
        //bone indexes which will influence this vertex
        int m_BoneIDs[MAX_BONE_INFLUENCE];
        //weights from each bone
        float m_Weights[MAX_BONE_INFLUENCE];
    };

    struct Texture {
        unsigned int id;
        std::string type;
        std::string path;
    };

    class ABSGL_API Mesh 
    {

    public:
        // mesh Data
        std::vector<Vertex>       vertices;
        std::vector<unsigned int> indices;
        std::vector<Texture>      textures;
        unsigned int VAO;

        // constructor
        Mesh();
        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
        void SetData(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);

        // render the mesh
        void Render(Shader& shader, glm::vec3& position);

    private:

        // render data 
        unsigned int VBO, EBO;

        // initializes all the buffer objects/arrays
        void setupMesh();
    };
}