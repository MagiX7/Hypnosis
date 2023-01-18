#include "IndexBuffer.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLIndexBuffer.h"

namespace Hypnosis {

	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::OPENGL:
			{
				return std::dynamic_pointer_cast<IndexBuffer>(std::make_shared<OpenGLIndexBuffer>(indices, count));
			}
		}
	}

}