#include "OpenGLContext.h"
#include "Hypnosis/Core/Log.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Hypnosis {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) : windowHandle(windowHandle)
	{

	}

	OpenGLContext::~OpenGLContext()
	{

	}

	bool OpenGLContext::Init()
	{
		glfwMakeContextCurrent(windowHandle);

		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		if (status == 0)
		{
			HS_CORE_INFO("[INFO] GLAD Loader Failed.");
			return false;
		}
		else
		{
			HS_CORE_INFO("[INFO] GLAD Loader Correct.");
			HS_CORE_INFO("[INFO] OpenGL Version: {0}", glGetString(GL_VERSION));
		}
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(windowHandle);
	}

}