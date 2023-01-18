#pragma once

#include "Hypnosis/Renderer/RendererAPI.h"

namespace Hypnosis {

	class OpenGLRendererAPI : public RendererAPI
	{
	public:

		virtual void Init() override;

		virtual void Clear(const glm::vec4& color) override;
		virtual void OnResize(int width, int height) override;
		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) override;
	};


}