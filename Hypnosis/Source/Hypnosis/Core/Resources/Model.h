#pragma once

#include "Mesh.h"
#include "Hypnosis/Core/TimeStep.h"

#include <glm/gtc/quaternion.hpp>
#include <string>
#include <vector>

namespace Hypnosis {


	class Model
	{
	public:
		Model(std::string path);
		~Model();

		void Update(TimeStep ts, float dx, float dy);
		void Draw() const;
		void ResetRotation();

		void AddMesh(Ref<Mesh> mesh);

		inline const glm::mat4& GetTransform() { return transform; }
		inline const std::string& GetName() { return name; }

		inline const std::vector<Ref<Mesh>>& GetMeshes() { return meshes; }

	private:
		std::string path;
		std::string name;
		std::vector<Ref<Mesh>> meshes;

		glm::mat4 transform;
		glm::quat rotation;
		
		//friend class ModelImporter;
	};

}