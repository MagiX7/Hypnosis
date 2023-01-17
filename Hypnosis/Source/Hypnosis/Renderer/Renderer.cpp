#include "Renderer.h"
#include "Hypnosis/Core/Log.h"

#include "VertexBuffer.h"
#include "Shader.h"

#include <glad/glad.h>

namespace Hypnosis {

	Renderer* Renderer::instance = nullptr;
	RendererAPI Renderer::rendererApi = RendererAPI::OPENGL;

	Renderer::Renderer()
	{
		
	}

	Renderer::~Renderer()
	{
	}

	Renderer* Renderer::GetInstance()
	{
		if (!instance)
			instance = new Renderer();

		return instance;
	}

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

	void Renderer::Clear(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Renderer::OnResize(int width, int height)
	{
		glViewport(0, 0, width, height);
	}

}