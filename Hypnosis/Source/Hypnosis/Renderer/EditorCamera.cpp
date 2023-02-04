#include "Hypnosis/Core/Core.h"
#include "EditorCamera.h"

#include "Hypnosis/Core/Input.h"
#include "Hypnosis/Core/KeyCodes.h"
#include "Hypnosis/Core/Log.h"

#include <glfw/glfw3.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

#include <functional>

namespace Hypnosis {

	EditorCamera::EditorCamera(float fov, float aspectRatio, float nearClip, float farClip)
		: fov(fov), aspectRatio(aspectRatio), nearClip(nearClip), farClip(farClip), projectionMatrix(glm::perspective(glm::radians(fov), aspectRatio, nearClip, farClip))
	{
		position = CalculatePosition();
		UpdateView();
	}

	void EditorCamera::UpdateProjection()
	{
		aspectRatio = viewportWidth / viewportHeight;
		projectionMatrix = glm::perspective(glm::radians(fov), aspectRatio, nearClip, farClip);
	}

	void EditorCamera::UpdateView()
	{
		// m_Yaw = m_Pitch = 0.0f; // Lock the camera's rotation
		//position = CalculatePosition();

		glm::quat orientation = GetOrientation();
		viewMatrix = glm::translate(glm::mat4(1.0f), position) * glm::toMat4(orientation);
		viewMatrix = glm::inverse(viewMatrix);
	}

	std::pair<float, float> EditorCamera::PanSpeed() const
	{
		float x = std::min(viewportWidth / 1000.0f, 2.4f); // max = 2.4f
		float xFactor = 0.0366f * (x * x) - 0.1778f * x + 0.3021f;

		float y = std::min(viewportHeight / 1000.0f, 2.4f); // max = 2.4f
		float yFactor = 0.0366f * (y * y) - 0.1778f * y + 0.3021f;

		return { xFactor, yFactor };
	}

	float EditorCamera::RotationSpeed() const
	{
		return 0.8f;
	}

	float EditorCamera::ZoomSpeed() const
	{
		float dist = distance * 0.2f;
		dist = std::max(dist, 0.0f);
		float speed = dist * dist;
		speed = std::min(speed, 100.0f); // max speed = 100
		return speed;
	}

	void EditorCamera::OnUpdate(TimeStep ts)
	{
		// TODO: Mouse Scroll is not working
		//if (Input::GetInstance()->IsKeyPressed(KEY_LEFT_ALT))
		if (Input::GetInstance()->IsMouseButtonPressed(MOUSE_RIGHT))
		{
			const glm::vec2& mouse{ Input::GetInstance()->GetMouseX(), Input::GetInstance()->GetMouseY() };
			glm::vec2 delta = (mouse - initialMousePosition) * 0.003f;
			initialMousePosition = mouse;
			
			if (Input::GetInstance()->IsMouseButtonPressed(MOUSE_MIDDLE))
				MousePan(delta);
			else if (Input::GetInstance()->IsMouseButtonPressed(MOUSE_LEFT))
				MouseRotate(delta);
			//else if (Input::GetInstance()->IsMouseButtonPressed(MOUSE_LEFT))
			//	MouseZoom(delta.y);
			
			float speed = 5.0f;
			if (Input::GetInstance()->IsKeyPressed(KEY_LEFT_SHIFT))
				speed *= 2;

			if (Input::GetInstance()->IsKeyPressed(KEY_W))
			{
				position += speed * ts * GetForwardDirection();
			}
			if (Input::GetInstance()->IsKeyPressed(KEY_S))
			{
				position -= speed * ts * GetForwardDirection();
			}
			if (Input::GetInstance()->IsKeyPressed(KEY_D))
			{
				position += speed * ts * GetRightDirection();
			}
			if (Input::GetInstance()->IsKeyPressed(KEY_A))
			{
				position -= speed * ts * GetRightDirection();
			}
			if (Input::GetInstance()->IsKeyPressed(KEY_Q))
			{
				position -= speed * ts * GetUpDirection();
			}
			if (Input::GetInstance()->IsKeyPressed(KEY_E))
			{
				position += speed * ts * GetUpDirection();
			}
		}

		UpdateView();
	}

	void EditorCamera::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(HS_BIND_EVENT_FN(EditorCamera::OnMouseScroll));
	}

	bool EditorCamera::OnMouseScroll(MouseScrolledEvent& e)
	{
		float delta = e.GetOffsetY() * 0.1f;
		MouseZoom(delta);
		UpdateView();
		return false;
	}

	void EditorCamera::MousePan(const glm::vec2& delta)
	{
		auto [xSpeed, ySpeed] = PanSpeed();
		focalPoint += -GetRightDirection() * delta.x * xSpeed * distance;
		focalPoint += GetUpDirection() * delta.y * ySpeed * distance;
	}

	void EditorCamera::MouseRotate(const glm::vec2& delta)
	{
		float yawSign = GetUpDirection().y < 0 ? -1.0f : 1.0f;
		yaw += yawSign * delta.x * RotationSpeed();
		pitch += delta.y * RotationSpeed();
	}

	void EditorCamera::MouseZoom(float delta)
	{
		distance -= delta * ZoomSpeed();
		if (distance < 1.0f)
		{
			focalPoint += GetForwardDirection();
			distance = 1.0f;
		}
	}

	glm::vec3 EditorCamera::GetUpDirection() const
	{
		return glm::rotate(GetOrientation(), glm::vec3(0.0f, 1.0f, 0.0f));
	}

	glm::vec3 EditorCamera::GetRightDirection() const
	{
		return glm::rotate(GetOrientation(), glm::vec3(1.0f, 0.0f, 0.0f));
	}

	glm::vec3 EditorCamera::GetForwardDirection() const
	{
		return glm::rotate(GetOrientation(), glm::vec3(0.0f, 0.0f, -1.0f));
	}

	glm::vec3 EditorCamera::CalculatePosition() const
	{
		return focalPoint - GetForwardDirection() * distance;
	}

	glm::quat EditorCamera::GetOrientation() const
	{
		return glm::quat(glm::vec3(-pitch, -yaw, 0.0f));
	}


}