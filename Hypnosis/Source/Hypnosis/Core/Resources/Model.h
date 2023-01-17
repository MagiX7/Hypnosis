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

		void AddMesh(Mesh* mesh);

		inline const glm::mat4& GetTransform() { return transform; }
		inline const std::string& GetName() { return name; }

	private:
		std::string path;
		std::string name;
		std::vector<Mesh*> meshes;

		glm::mat4 transform;
		glm::quat rotation;
		
		//friend class ModelImporter;
	};

}