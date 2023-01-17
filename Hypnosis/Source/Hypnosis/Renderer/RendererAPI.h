#pragma once

#include "VertexArray.h"

#include <glm/vec4.hpp>

#include <memory>

namespace Hypnosis {

	class RendererAPI
	{
	public:
		enum class API
		{
			NONE = 0,
			OPENGL,
			VULKAN
		};

	public:
		virtual void Clear(const glm::vec4& color) = 0;

		virtual void OnResize(int width, int height) = 0;

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) = 0;

		static inline API GetAPI() { return api; }

	private:
		static API api;

	};

}