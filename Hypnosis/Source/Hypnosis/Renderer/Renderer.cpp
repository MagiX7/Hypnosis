#include "Renderer.h"
#include "Hypnosis/Core/Log.h"

#include "VertexBuffer.h"
#include "Shader.h"

#include <glad/glad.h>

namespace Hypnosis {

	//Renderer* Renderer::instance = nullptr;

	Renderer::Renderer()
	{
	}

	Renderer::~Renderer()
	{
	}

	void Renderer::Init()
	{
		RenderCommand::Init();
	}

	void Renderer::ShutDown()
	{
	}

	void Renderer::BeginScene()
	{

	}

	void Renderer::EndScene()
	{

	}

	void Renderer::Submit(const Ref<VertexArray>& vertexArray)
	{
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}

}