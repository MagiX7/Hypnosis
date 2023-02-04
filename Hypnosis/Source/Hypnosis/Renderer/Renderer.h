#pragma once

#include "RenderCommand.h"
#include "Shader.h"
#include "Texture2D.h"

#include <glm/glm.hpp>
#include <memory>

namespace Hypnosis {;

	class Model;

	class Renderer
	{
	public:
		//static Renderer* GetInstance();

		static void Init();
		static void ShutDown();
		//static void Clear(const glm::vec4& color);
		//static void OnResize(int width, int height);

		static void BeginScene();
		static void EndScene();

		static void Submit(const Ref<VertexArray>& vertexArray);
		//static void Submit(Model* model);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }


	private:
		Renderer();
		virtual ~Renderer();

		Renderer(const Renderer&) = delete;
		Renderer& operator=(const Renderer&) = delete;

	private:
		//static Renderer* instance;
	};
}