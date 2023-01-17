#pragma once

#include "Hypnosis/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Hypnosis {

	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);
		virtual ~OpenGLContext();

		virtual bool Init() override;
		virtual void SwapBuffers() override;

	private:

		GLFWwindow* windowHandle;
	};


}