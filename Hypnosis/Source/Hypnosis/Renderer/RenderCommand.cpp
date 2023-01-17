#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Hypnosis {

	// TODO: This should be changed when the context is created
	RendererAPI* RenderCommand::rendererAPI = new OpenGLRendererAPI();

}