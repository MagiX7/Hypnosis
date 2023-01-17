#pragma once

#include "Hypnosis.h"

namespace Hypnosis {

	class EditorLayer : public EngineLayer
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
		std::shared_ptr<FrameBuffer> fbo;

		glm::vec2 viewportSize;
	};
}