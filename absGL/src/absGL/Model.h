#pragma once

#include "Core.h"
#include "Mesh.h"
#include "Shader.h"

#include "assimp/Importer.hpp"
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <glm/glm.hpp>

#include <vector>

namespace absGL
{
    class Renderer;

    class ABSGL_API Model
    {

    public:

        void SetPosition(float x, float y, float z);
        inline void SetShader(Shader* shader) { m_CurrentShader = shader; }

        // draws the model, and thus all its meshes
        void Render();

        std::vector<Texture> m_Textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
        std::vector<Mesh>    m_Meshes;
        std::string m_Directory;
        bool m_GammaCorrection;

        // constructor, expects a filepath to a 3D model.
        Model(std::string const& path, Shader* startShader, bool gamma = false);

    private:

        // loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.
        void loadModel(std::string const& path);

        // processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
        void processNode(aiNode* node, const aiScene* scene);

        Mesh processMesh(aiMesh* mesh, const aiScene* scene);

        // checks all material textures of a given type and loads the textures if they're not loaded yet.
        // the required info is returned as a Texture struct.
        std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);

        unsigned int TextureFromFile(const char* path, const std::string& m_Directory, bool gamma);

        Shader* m_CurrentShader = nullptr;
        glm::vec3 m_Position;

    };
}