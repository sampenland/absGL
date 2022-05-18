#pragma once
#include "Core.h"
#include "Shader.h"
#include "Vector.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <string>

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
        Vector<Vertex>       vertices;
        Vector<unsigned int> indices;
        Vector<Texture>      textures;
        unsigned int VAO;

        // constructor
        Mesh();
        Mesh(Vector<Vertex> vertices, Vector<unsigned int> indices, Vector<Texture> textures);
        void SetData(absGL::Vector<Vertex> vertices, absGL::Vector<unsigned int> indices, absGL::Vector<Texture> textures);

        // render the mesh
        void Render(Shader& shader);

    private:

        // render data 
        unsigned int VBO, EBO;

        // initializes all the buffer objects/arrays
        void setupMesh();
    };
}