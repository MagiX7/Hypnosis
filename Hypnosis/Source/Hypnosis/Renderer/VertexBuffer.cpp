#include "VertexBuffer.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLVertexBuffer.h"

namespace Hypnosis {

	Ref<VertexBuffer> VertexBuffer::Create(Vertex* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::OPENGL:
			{
				return std::dynamic_pointer_cast<VertexBuffer>(std::make_shared<OpenGLVertexBuffer>(vertices, size));
			}
		}
	}
}