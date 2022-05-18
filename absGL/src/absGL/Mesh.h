#pragma once
#include "Core.h"
#include "Shader.h"

#include "vendor/glm/glm.hpp"

#include <vector>
#include <string>

namespace absGL
{
	struct ABSGL_API Vertex
	{
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec2 TexCoords;
		glm::vec3 Tangent;
		glm::vec3 Bitangent;
	};

	struct ABSGL_API Texture 
	{
		unsigned int m_RenderID = 0;
		std::string Type;
		std::string Path;
	};

	class ABSGL_API Mesh
	{

	public:

		std::vector<Vertex>       m_Vertices;
		std::vector<unsigned int> m_Indices;
		std::vector<Texture>      m_Textures;

		Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
		void Render(Shader& shader);

	private:

		unsigned int m_VAORenderID;
		unsigned int m_VBORenderID;
		unsigned int m_EBORenderID;

		void SetupMesh();
	};
}