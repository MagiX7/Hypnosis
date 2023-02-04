#pragma once

#include "Hypnosis/Core/Timestep.h"
#include "Hypnosis/Events/Event.h"
#include "Hypnosis/Events/MouseEvent.h"
#include "Hypnosis/Events/ApplicationEvent.h"

#include <glm/glm.hpp>

namespace Hypnosis {

	class EditorCamera
	{
	public:
		EditorCamera() = default;
		EditorCamera(float fov, float aspectRatio, float nearClip, float farClip);

		void OnUpdate(TimeStep ts);
		void OnEvent(Event& e);

		inline float GetDistance() const { return distance; }
		inline void SetDistance(float value) { distance = value; }

		inline void SetViewportSize(float width, float height) { viewportWidth = width; viewportHeight = height; UpdateProjection(); }

		const glm::mat4& GetViewMatrix() const { return viewMatrix; }
		const glm::mat4& GetProjectionMatrix() const { return projectionMatrix; }
		glm::mat4 GetViewProjection() const { return projectionMatrix * viewMatrix; }

		glm::vec3 GetUpDirection() const;
		glm::vec3 GetRightDirection() const;
		glm::vec3 GetForwardDirection() const;
		const glm::vec3& GetPosition() const { return position; }
		glm::quat GetOrientation() const;

		float GetPitch() const { return pitch; }
		float GetYaw() const { return yaw; }
	private:
		void UpdateProjection();
		void UpdateView();

		bool OnMouseScroll(MouseScrolledEvent& e);

		void MousePan(const glm::vec2& delta);
		void MouseRotate(const glm::vec2& delta);
		void MouseZoom(float delta);

		glm::vec3 CalculatePosition() const;

		std::pair<float, float> PanSpeed() const;
		float RotationSpeed() const;
		float ZoomSpeed() const;
	private:
		float fov = 45.0f, aspectRatio = 1.778f, nearClip = 0.1f, farClip = 1000.0f;

		glm::mat4 viewMatrix;
		glm::mat4 projectionMatrix;
		glm::vec3 position = { 0.0f, 0.0f, 0.0f };
		glm::vec3 focalPoint = { 0.0f, 0.0f, 0.0f };

		glm::vec2 initialMousePosition = { 0.0f, 0.0f };

		float distance = 10.0f;
		float pitch = 0.0f, yaw = 0.0f;

		float viewportWidth = 1280, viewportHeight = 720;
	};

}
