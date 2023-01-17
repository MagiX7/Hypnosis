#include "FrameBuffer.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLFrameBuffer.h"

namespace Hypnosis {

	std::shared_ptr<FrameBuffer> FrameBuffer::Create(int w, int h)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::OPENGL:
			{
				return std::dynamic_pointer_cast<FrameBuffer>(std::make_shared<OpenGLFrameBuffer>(w, h));
			}
		}
	}

}