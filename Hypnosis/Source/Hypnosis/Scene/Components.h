#pragma once

#include "Hypnosis/Core/Core.h"
#include "Hypnosis/Core/Resources/Model.h"
#include "Hypnosis/Scene/SceneCamera.h"

#include <glm/glm.hpp>

namespace Hypnosis {

	struct TransformComponent
	{
		//glm::mat4 transform = glm::mat4(1.0f);

		glm::vec3 position = glm::vec3(0);
		glm::vec3 rotation = glm::vec3(0);
		glm::vec3 scale = glm::vec3(1);


		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const glm::vec3& pos) : position(pos) {}

		glm::mat4 GetTransform() const
		{
			glm::mat4 rot = glm::rotate(glm::mat4(1.0f), rotation.x, {1,0,0})
				* glm::rotate(glm::mat4(1.0f), rotation.y, { 0,1,0 })
				* glm::rotate(glm::mat4(1.0f), rotation.z, { 0,0,1 });

			return glm::translate(glm::mat4(1.0f), position) * rot * glm::scale(glm::mat4(1.0f), scale);
		}
	};

	struct TagComponent
	{
		std::string tag;

		TagComponent() = default;
		TagComponent(const TagComponent&) = default;
		TagComponent(const std::string& tag) : tag(tag) {}
	};

	struct MeshComponent
	{
		Ref<Mesh> mesh;
		MeshComponent() = default;
		MeshComponent(const MeshComponent&) = default;
		MeshComponent(Ref<Mesh> mesh) : mesh(mesh) {}

		operator Ref<Mesh> () { return mesh; }
		operator const Ref<Mesh>& () { return mesh; }

	};

	struct MaterialComponent
	{
		//Ref<Material> material;

		MaterialComponent() = default;
		MaterialComponent(const MaterialComponent&) = default;
		//MaterialComponent(Ref<Material> mat) : material(mat)

	};

	struct LightComponent
	{
		glm::vec3 direction;
		glm::vec3 color;
		float intensity = 1.0f;

		LightComponent() = default;
		LightComponent(const LightComponent&) = default;
		LightComponent(glm::vec3 dir, glm::vec4 color) : direction(dir), color(color) {}

	};

	struct CameraComponent
	{
		SceneCamera camera;
		bool isPrimary = true;
		bool fixedAspectRatio = false; // This is for handle resizing or not, depending on the user interests. Still to implement

		CameraComponent() = default;
		CameraComponent(const CameraComponent&) = default;
	};


}