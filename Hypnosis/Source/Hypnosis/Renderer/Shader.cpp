#include "Shader.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Hypnosis {

	Ref<Shader> Shader::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::OPENGL:
			{
				return std::dynamic_pointer_cast<Shader>(std::make_shared<OpenGLShader>(path));
			}
		}
	}
}