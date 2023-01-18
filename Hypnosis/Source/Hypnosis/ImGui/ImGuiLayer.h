#pragma once

#include "Hypnosis/Core/Layer.h"

#include "Hypnosis/Events/ApplicationEvent.h"
#include "Hypnosis/Events/Event.h"
#include "Hypnosis/Events/KeyEvent.h"
#include "Hypnosis/Events/MouseEvent.h"


namespace Hypnosis {

	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void Begin();
		void End();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

	private:
		void SetStyle();

	private:
		float time = 0;
	};


}