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

	/*Renderer* Renderer::GetInstance()
	{
		if (!instance)
			instance = new Renderer();

		return instance;
	}*/

	void Renderer::Init()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_CULL_FACE);
		glDepthFunc(GL_LEQUAL);
		glLineWidth(2.0f);
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

	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray)
	{
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}

}