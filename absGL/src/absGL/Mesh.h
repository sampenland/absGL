#pragma once
#include "Shader.h"
#include "Vertex.h"
#include "Texture.h"

#include <vector>

namespace absGL
{
    class Model;

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
        void Render(Shader& shader, Model& modelRef);

    private:

        // render data 
        unsigned int VBO, EBO;

        // initializes all the buffer objects/arrays
        void setupMesh();
    };
}