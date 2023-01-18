#pragma once

#include "Hypnosis/Core/Resources/Model.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

//
//class aiNode;
//class aiScene;
//class aiMesh;

namespace Hypnosis {

	class ModelImporter
	{
	public:
		static void ImportModel(std::string path, Model& model);

	private:
		static void ProcessNode(aiNode* node, const aiScene* scene, Model& model);
		static Ref<Mesh> ProcessMesh(aiMesh* node, const aiScene* scene);
		static void ComputeTangentsAndBiTangents(std::vector<Vertex>& vertices, unsigned int indicesCount);
	};

}