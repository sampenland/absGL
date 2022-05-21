/*

    When exporting obj models from Blender,
    make sure to go into the .mtl file and remove
    the absolute path to the texture files and make it
    just the texture name. Then store that texture in 
    the same folder as the .obj file 

    or set texture paths to be relative to .obj folder
    location

*/
#pragma once

#include "Core.h"
#include "Shader.h"
#include "Material.h"
#include "Texture.h"
#include "Mesh.h"

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

        inline glm::vec3 GetPosition() const { return m_Position; }
        inline float GetShininess() const { return m_Material->Shininess; }

        // draws the model, and thus all its meshes
        void Render();
        void Render(Shader* shader);

        std::vector<Texture> m_Textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
        std::vector<Mesh>    m_Meshes;
        std::string m_Directory;
        bool m_GammaCorrection;

        // constructor, expects a filepath to a 3D model.
        Model(std::string const& path, Shader* startShader, float shininess = 32, bool gamma = false);

        // Copy constructor
        Model(Model& m);

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
        Material* m_Material;
        glm::vec3 m_Position;

    };
}