#include "EditorLayer.h"

#include <ImGui/imgui.h>

namespace Hypnosis {

	EditorLayer::EditorLayer()
	{

	}

	EditorLayer::~EditorLayer()
	{

	}

	void EditorLayer::OnAttach()
	{

	}

	void EditorLayer::OnDetach()
	{

	}

	void EditorLayer::OnUpdate(const TimeStep ts)
	{

	}

	void EditorLayer::OnImGuiRender()
	{
		ImGui::Begin("Hello");
		ImGui::End();
	}

	void EditorLayer::OnEvent(Event& e)
	{

	}

}