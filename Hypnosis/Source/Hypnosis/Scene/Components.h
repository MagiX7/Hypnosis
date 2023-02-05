#pragma once

#include "Hypnosis/Core/Core.h"
#include "Hypnosis/Core/Resources/Model.h"
#include "Hypnosis/Scene/SceneCamera.h"

#include <glm/glm.hpp>

namespace Hypnosis {

	struct TransformComponent
	{
		glm::mat4 transform = glm::mat4(1.0f);

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const glm::mat4& transformMatrix) : transform(transformMatrix) {}

		operator glm::mat4& () { return transform; }
		operator const glm::mat4& const () { return transform; }

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
		bool fixedAspectRatio = false; // This is for handle resizing or not, depending on the user interests

		CameraComponent() = default;
		CameraComponent(const CameraComponent&) = default;
	};


}