#pragma once

#include <glm/glm.hpp>

namespace Hypnosis {

	class Camera
	{
	public:
		Camera() {};
		Camera(const glm::mat4& projectionMatrix) : projection(projectionMatrix) {}
		virtual ~Camera() {}

		const glm::mat4& GetProjection() { return projection; }

	protected:
		glm::mat4 projection = glm::mat4(1.0f);
	};

}