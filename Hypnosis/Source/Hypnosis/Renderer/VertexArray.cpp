#include "VertexArray.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Hypnosis {

	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::OPENGL:
			{
				return std::dynamic_pointer_cast<VertexArray>(std::make_shared<OpenGLVertexArray>());
			}
		}
	}


}