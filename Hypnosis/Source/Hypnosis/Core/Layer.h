#pragma once

#include "Hypnosis/Events/Event.h"
#include "TimeStep.h"

#include <string>

namespace Hypnosis {

	class Layer
	{
	public:
		Layer(const std::string& name = "Default Layer", bool enabled = true);
		virtual ~Layer();

		virtual void OnAttach() {};
		virtual void OnDetach() {};
		virtual void OnUpdate(const TimeStep ts) {};
		virtual void OnImGuiRender() {};
		virtual void OnEvent(Event& e) {};

		inline const std::string& GetName() { return name; }

		inline bool IsEnabled() { return enabled; }
		void SetEnabled(bool value) { enabled = value; }

	private:
		std::string name;
		bool enabled;
	};

}