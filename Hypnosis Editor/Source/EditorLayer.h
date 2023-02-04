#pragma once

#include "Hypnosis.h"

namespace Hypnosis {

	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		virtual ~EditorLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnUpdate(const TimeStep ts) override;
		virtual void OnImGuiRender() override;
		virtual void OnEvent(Event& e) override;

	private:
		Model* model;
		Ref<FrameBuffer> fbo;
		Ref<Shader> shader;

		Ref<Texture2D> diffuse;
		Ref<Texture2D> normals;
		Ref<Texture2D> roughness;
		Ref<Texture2D> metallic;

		glm::vec2 viewportSize;

		Ref<Scene> currentScene;
		Entity dirLight;

		EditorCamera camera;
	};
}