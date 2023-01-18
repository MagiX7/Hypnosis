#include "OpenGLRendererAPI.h"

#include <glad/glad.h>

namespace Hypnosis {

	void OpenGLRendererAPI::Init()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_CULL_FACE);
		glDepthFunc(GL_LEQUAL);
	}

	void OpenGLRendererAPI::Clear(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::OnResize(int width, int height)
	{
		glViewport(0, 0, width, height);
	}

	void OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray)
	{
		vertexArray->GetIndexBuffer()->Bind();
		glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, 0);
	}

}