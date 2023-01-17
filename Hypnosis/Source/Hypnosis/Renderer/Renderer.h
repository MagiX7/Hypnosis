#pragma once

#include <glm/glm.hpp>
#include <memory>

namespace Hypnosis {

	enum class RendererAPI
	{
		NONE = 0,
		OPENGL,
		VULKAN
	};

	class Renderer
	{
	public:
		static Renderer* GetInstance();

		void Init();
		void ShutDown();
		void Clear(const glm::vec4& color);
		void OnResize(int width, int height);

		inline static RendererAPI GetAPI() { return rendererApi; }

	private:
		Renderer();
		virtual ~Renderer();

		Renderer(const Renderer&) = delete;
		Renderer& operator=(const Renderer&) = delete;

	private:
		static Renderer* instance;

		static RendererAPI rendererApi;

	};
}