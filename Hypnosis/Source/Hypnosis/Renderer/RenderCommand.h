#pragma once

#include "RendererAPI.h"

namespace Hypnosis {

	class RenderCommand
	{
	public:

		inline static void Init() { rendererAPI->Init(); }

		inline static void Clear(const glm::vec4& color) { rendererAPI->Clear(color); }
		inline static void OnResize(int width, int height) { rendererAPI->OnResize(width, height); }

		inline static void DrawIndexed(const Ref<VertexArray>& vertexArray)
		{
			rendererAPI->DrawIndexed(vertexArray);
		}

	private:
		static RendererAPI* rendererAPI;
	};

}
