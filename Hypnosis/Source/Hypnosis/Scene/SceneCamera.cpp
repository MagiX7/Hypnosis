#include "SceneCamera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Hypnosis {

	SceneCamera::SceneCamera()
	{
		RecalculateProjection();
	}

	void SceneCamera::SetPerspective(float verticalFov, float nearClip, float farClip)
	{
		projectionType = ProjectionType::PERSPECTIVE;
		
		yFov = verticalFov;
		perspectiveNear = nearClip;
		perspectiveFar = farClip;

		RecalculateProjection();
	}

	void SceneCamera::SetOrthographic(float size, float nearClip, float farClip)
	{
		projectionType = ProjectionType::ORTHOGRAPHIC;
		
		orthoSize = size;
		orthoNear = nearClip;
		orthoFar = farClip;

		RecalculateProjection();
	}

	void SceneCamera::SetViewportSize(uint32_t width, uint32_t height)
	{
		aspectRatio = (float)width / glm::max((float)height, 0.001f);
		RecalculateProjection();
	}

	void SceneCamera::RecalculateProjection()
	{
		if (projectionType == ProjectionType::PERSPECTIVE)
		{
			projection = glm::perspective(glm::radians(yFov), aspectRatio, perspectiveNear, perspectiveFar);
		}
		else if (projectionType == ProjectionType::ORTHOGRAPHIC)
		{
			float left = -orthoSize * aspectRatio * 0.5f;
			float right = orthoSize * aspectRatio * 0.5f;
			float bottom = -orthoSize * 0.5f;
			float top = orthoSize * 0.5f;

			projection = glm::ortho(left, right, bottom, top, orthoNear, orthoFar);
		}

	}

}