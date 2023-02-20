#include "EditorLayer.h"

#include <ImGui/imgui.h>

namespace Hypnosis {

	EditorLayer::EditorLayer() //: camera(PerspectiveCamera({ 0,0,2.5 }, { 0,0,0 }, 60.0f, 1280.0f / 720.0f))
	{
		editorCamera = EditorCamera(60.0f, 1280.0f / 720.0f, 0.1f, 1000.0f);
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

		shader = Hypnosis::Shader::Create("Assets/Shaders/PBR.shader");

		diffuse = Hypnosis::Texture2D::Create("Settings/white.png");
		normals = Hypnosis::Texture2D::Create("Settings/white.png");
		roughness = Hypnosis::Texture2D::Create("Settings/white.png");
		metallic = Hypnosis::Texture2D::Create("Settings/white.png");

		cubeEntity = currentScene->CreateEntity("Cube");

		dirLight = currentScene->CreateEntity("Directional Light");
		dirLight.AddComponent<LightComponent>(glm::vec3(1, 1, 1), glm::vec4(1));

		cameraEntity = currentScene->CreateEntity("Camera Entity");
		cameraEntity.AddComponent<CameraComponent>();


		sceneHierarchyPanel.SetContext(currentScene);
	}

	void EditorLayer::OnDetach()
	{

	}

	void EditorLayer::OnUpdate(const TimeStep ts)
	{
		editorCamera.OnUpdate(ts);

		Renderer::BeginScene();
		{
			fbo->Bind();
			{
				RenderCommand::Clear({ 0.15, 0.15, 0.15, 1 });
				
				// Draw Scene
				//currentScene->OnUpdate(ts);

				shader->Bind();
				shader->SetUniformMatrix4f("view", editorCamera.GetViewMatrix());
				shader->SetUniformMatrix4f("projection", editorCamera.GetProjectionMatrix());

				//shader->SetUniformMatrix4f("view", glm::inverse(cameraEntity.GetComponent<TransformComponent>().GetTransform()));
				//shader->SetUniformMatrix4f("projection", cameraEntity.GetComponent<CameraComponent>().camera.GetProjection());

				shader->SetUniformMatrix4f("model", cubeEntity.GetComponent<TransformComponent>().GetTransform());
				//shader->SetUniformMatrix4f("model", model->GetTransform());

				auto light = dirLight.GetComponent<LightComponent>();
				shader->SetUniformVec3f("dirLight.direction", light.direction);
				shader->SetUniformVec3f("dirLight.color", light.color);
				shader->SetUniform1f("dirLight.intensity", light.intensity);

				//shader->SetUniformVec3f("camPos", editorCamera.GetPosition());
				shader->SetUniformVec3f("camPos", cameraEntity.GetComponent<TransformComponent>().position);


				diffuse->Bind(0);
				shader->SetUniform1i("diffuseTexture", 0);

				normals->Bind(1);
				shader->SetUniform1i("normalsTexture", 1);

				metallic->Bind(2);
				shader->SetUniform1i("metallicTexture", 2);
				
				roughness->Bind(3);
				shader->SetUniform1i("roughnessTexture", 3);


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
			editorCamera.SetViewportSize(dimensions.x, dimensions.y);
			cameraEntity.GetComponent<CameraComponent>().camera.SetViewportSize((uint32_t)dimensions.x, (uint32_t)dimensions.y);
			currentScene->OnViewportResize(dimensions.x, dimensions.y);

			HS_TRACE("Viewport Resized");
			viewportSize = { dimensions.x, dimensions.y };
		}

		ImGui::Image((ImTextureID*)fbo->GetColorId(), { viewportSize.x, viewportSize.y }, { 0,1 }, { 1,0 });


		ImGui::End();


		sceneHierarchyPanel.OnImGuiRender();

	}

	void EditorLayer::OnEvent(Event& e)
	{
		editorCamera.OnEvent(e);
	}

}