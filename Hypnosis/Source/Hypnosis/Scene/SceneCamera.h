#pragma once

#include "Hypnosis/Renderer/Camera.h"

namespace Hypnosis {

	// This is what is shown in the inspector
	class SceneCamera : public Camera
	{
	public:
		enum class ProjectionType { PERSPECTIVE = 0, ORTHOGRAPHIC = 1, };

	public:
		SceneCamera();
		virtual ~SceneCamera() {}

		void SetPerspective(float verticalFov, float nearClip, float farClip);
		void SetOrthographic(float size, float nearClip, float farClip);

		void SetViewportSize(uint32_t width, uint32_t height);

		void SetProjectionType(ProjectionType type) { projectionType = type; RecalculateProjection();  }
		ProjectionType GetProjectionType() const { return projectionType; }

		// Perspective Methods
		float GetPerspectiveNearClip() { return perspectiveNear; }
		void SetPerspectiveNearClip(float value) { perspectiveNear = value; RecalculateProjection(); }

		float GetPerspectiveFarClip() { return perspectiveFar; }
		void SetPerspectiveFarClip(float value) { perspectiveFar = value; RecalculateProjection(); }

		float GetVerticalFov() { return yFov; }
		void SetVerticalFov(float value) { yFov = value; RecalculateProjection(); }

		// Orthographic Methods
		float GetOrthographicFarClip() { return orthoFar; }
		void SetOrthographicFarClip(float value) { orthoFar = value; RecalculateProjection(); }

		float GetOrthographicNearClip() { return orthoNear; }
		void SetOrthographicNearClip(float value) { orthoNear = value; RecalculateProjection();  }
		
		float GetOrthographicSize() { return orthoSize; }
		void SetOrthographicSize(float value) { orthoSize = value; RecalculateProjection();  }

		float GetAspectRatio() { return aspectRatio; }
		void SetAspectRatio(float value) {
			aspectRatio = value; RecalculateProjection(); }

	private:
		void RecalculateProjection();

	private:
		ProjectionType projectionType = ProjectionType::PERSPECTIVE;

		float yFov = 45.0f;
		float perspectiveNear = 0.01f;
		float perspectiveFar = 1000.0f;

		float orthoSize = 10.0f;
		float orthoNear = -1;
		float orthoFar = 1;

		float aspectRatio = 0.0f;
	};

}