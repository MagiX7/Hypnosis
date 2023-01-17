#include "VertexArray.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Hypnosis {

	std::shared_ptr<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::OPENGL:
			{
				return std::dynamic_pointer_cast<VertexArray>(std::make_shared<OpenGLVertexArray>());
			}
		}
	}


}