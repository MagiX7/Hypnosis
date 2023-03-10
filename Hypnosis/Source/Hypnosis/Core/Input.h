#pragma once

#include "KeyCodes.h"
#include "Hypnosis/Events/Event.h"
#include "Hypnosis/Events/MouseEvent.h"

#include <glm/vec2.hpp>

#include <utility>

namespace Hypnosis {

	class Input
	{
	public:
		static Input* GetInstance();

		bool IsKeyPressed(int keycode);
		bool IsMouseButtonPressed(int button);

		float GetMouseX();
		float GetMouseY();
		float GetMouseMotionX();
		float GetMouseMotionY();
		glm::vec2 GetMousePosition();
		inline float GetMouseScrolDx() { return deltaXScroll; }
		inline float GetMouseScrolDy() { return deltaYScroll; }

		void OnEvent(Event& e);

		void ResetScrollStats();

	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);

	private:
		static Input* instance;

		float deltaXScroll;
		float deltaYScroll;

		float lastMousePosX = 0;
		float lastMousePosY = 0;
		double x, y;
	};	

}