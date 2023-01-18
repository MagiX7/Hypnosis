#include "Texture2D.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLTexture2D.h"

namespace Hypnosis {

	Ref<Hypnosis::Texture2D> Hypnosis::Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::OPENGL:
			{
				return std::dynamic_pointer_cast<Texture2D>(std::make_shared<OpenGLTexture2D>(path));
			}
		}
	}

}

