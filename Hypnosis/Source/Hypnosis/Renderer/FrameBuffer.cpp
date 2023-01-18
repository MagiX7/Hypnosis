#include "FrameBuffer.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLFrameBuffer.h"

namespace Hypnosis {

	Ref<FrameBuffer> FrameBuffer::Create(int w, int h)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::OPENGL:
			{
				return std::dynamic_pointer_cast<FrameBuffer>(std::make_shared<OpenGLFrameBuffer>(w, h));
			}
		}
	}

}