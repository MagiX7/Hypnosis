#pragma once

#include "Hypnosis/Renderer/RendererAPI.h"

namespace Hypnosis {

	class OpenGLRendererAPI : public RendererAPI
	{
	public:

		virtual void Clear(const glm::vec4& color) override;
		virtual void OnResize(int width, int height) override;
		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;
	};


}