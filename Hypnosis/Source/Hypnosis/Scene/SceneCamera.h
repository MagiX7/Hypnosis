#pragma once

#include "Hypnosis/Renderer/Camera.h"

namespace Hypnosis {

	// This is what is shown in the inspector
	class SceneCamera : public Camera
	{
	public:
		SceneCamera();
		virtual ~SceneCamera() {}

		void SetPerspective(float yFov, float aspectRatio);
		void SetViewportSize(uint32_t width, uint32_t height);

	private:
		void RecalculateProjection();

	private:
		float yFov = 60.0f;
		float aspectRatio = 0.0f;
		float near = 0.1f;
		float far = 1000.0f;

	};

}