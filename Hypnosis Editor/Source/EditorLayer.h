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

		glm::vec2 viewportSize;

		EditorCamera camera;
	};
}