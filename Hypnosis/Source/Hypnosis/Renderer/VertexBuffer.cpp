#include "VertexBuffer.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLVertexBuffer.h"
#include "Platform/OpenGL/OpenGLIndexBuffer.h"

namespace Hypnosis {

	std::shared_ptr<VertexBuffer> VertexBuffer::Create(Vertex* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::OPENGL:
			{
				return std::dynamic_pointer_cast<VertexBuffer>(std::make_shared<OpenGLVertexBuffer>(vertices, size));
			}
		}
	}
}