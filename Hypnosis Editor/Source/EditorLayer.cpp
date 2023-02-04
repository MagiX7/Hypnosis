#include "EditorLayer.h"

#include <ImGui/imgui.h>

namespace Hypnosis {

	EditorLayer::EditorLayer() //: camera(PerspectiveCamera({ 0,0,2.5 }, { 0,0,0 }, 60.0f, 1280.0f / 720.0f))
	{
		camera = EditorCamera(60.0f, 1280.0f / 720.0f, 0.1f, 1000.0f);
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

		currentScene = CreateRef<Scene>();
		auto cubeEntity = currentScene->CreateEntity("Cube");

		shader = Hypnosis::Shader::Create("Assets/Shaders/PBR.shader");

		diffuse = Hypnosis::Texture2D::Create("Settings/white.png");
		normals = Hypnosis::Texture2D::Create("Settings/white.png");
		roughness = Hypnosis::Texture2D::Create("Settings/white.png");
		metallic = Hypnosis::Texture2D::Create("Settings/white.png");

		dirLight = currentScene->CreateEntity("Directional Light");
		dirLight.AddComponent<LightComponent>(glm::vec3(1, 1, 1), glm::vec4(1));
	}

	void EditorLayer::OnDetach()
	{

	}

	void EditorLayer::OnUpdate(const TimeStep ts)
	{
		camera.OnUpdate(ts);		

		Renderer::BeginScene();
		{
			fbo->Bind();
			{
				RenderCommand::Clear({ 0.15, 0.15, 0.15, 1 });
				
				// Draw Scene
				//currentScene->OnUpdate(ts);

				shader->Bind();
				shader->SetUniformMatrix4f("view", camera.GetViewMatrix());
				shader->SetUniformMatrix4f("projection", camera.GetProjectionMatrix());
				shader->SetUniformMatrix4f("model", model->GetTransform());

				auto light = dirLight.GetComponent<LightComponent>();
				shader->SetUniformVec3f("dirLight.direction", light.direction);
				shader->SetUniformVec3f("dirLight.color", light.color);
				shader->SetUniform1f("dirLight.intensity", light.intensity);

				diffuse->Bind();
				shader->SetUniform1i("diffuse", 0);

				normals->Bind(1);
				shader->SetUniform1i("normals", 1);

				metallic->Bind(2);
				shader->SetUniform1i("metallic", 2);
				
				roughness->Bind(3);
				shader->SetUniform1i("roughness", 3);


				model->Draw();
				shader->Unbind();
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
			camera.SetViewportSize(dimensions.x, dimensions.y);
			ZN_TRACE("Viewport Resized");
			viewportSize = { dimensions.x, dimensions.y };
		}

		ImGui::Image((ImTextureID*)fbo->GetColorId(), { viewportSize.x, viewportSize.y }, { 0,1 }, { 1,0 });



		ImGui::End();
	}

	void EditorLayer::OnEvent(Event& e)
	{
		camera.OnEvent(e);
	}

}