#include "SceneCamera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Hypnosis {

	SceneCamera::SceneCamera()
	{
		RecalculateProjection();
	}

	void SceneCamera::SetPerspective(float yFov, float aspectRatio)
	{
		this->yFov = yFov;
		this->aspectRatio = aspectRatio;
		RecalculateProjection();
	}

	void SceneCamera::SetViewportSize(uint32_t width, uint32_t height)
	{
		aspectRatio = (float)width / (float)height;
		RecalculateProjection();
	}

	void SceneCamera::RecalculateProjection()
	{
		projection = glm::perspective(glm::radians(yFov), aspectRatio, near, far);
	}

}