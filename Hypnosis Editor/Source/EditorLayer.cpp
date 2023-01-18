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
		//model = new Model("Assets/Models/Cerberus.fbx");
		model = new Model("Assets/Models/Cube.fbx");
		int w = Application::GetInstance().GetWindow().GetWidth();
		int h = Application::GetInstance().GetWindow().GetHeight();
		fbo = FrameBuffer::Create(w, h);
	}

	void EditorLayer::OnDetach()
	{

	}

	void EditorLayer::OnUpdate(const TimeStep ts)
	{
		Renderer::BeginScene();
		{
			fbo->Bind();
			{
				RenderCommand::Clear({ 0.15, 0.15, 0.15, 1 });
				for (auto& mesh : model->GetMeshes())
				{
					Renderer::Submit(mesh->GetVertexArray());
				}
			}
			fbo->Unbind();
		}
		Renderer::EndScene();
	}

	void EditorLayer::OnImGuiRender()
	{
		ImGui::Begin("Viewport");
		
		ImVec2 dimensions = ImGui::GetContentRegionAvail();
		if (viewportSize.x != dimensions.x || viewportSize.y != dimensions.y)
		{
			fbo->Resize(dimensions.x, dimensions.y);
			RenderCommand::OnResize(dimensions.x, dimensions.y);
			//camera.SetApsectRatio(dimensions.x / dimensions.y);
			ZN_TRACE("Viewport Resized");
			viewportSize = { dimensions.x, dimensions.y };
		}

		ImGui::Image((ImTextureID*)fbo->GetColorId(), { viewportSize.x, viewportSize.y }, { 0,1 }, { 1,0 });



		ImGui::End();
	}

	void EditorLayer::OnEvent(Event& e)
	{

	}

}