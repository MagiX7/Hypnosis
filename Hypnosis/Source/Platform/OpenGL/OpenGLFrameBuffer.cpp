#include "OpenGLFramebuffer.h"
#include "Hypnosis/Core/Log.h"

#include <glad/glad.h>

namespace Hypnosis {

	OpenGLFrameBuffer::OpenGLFrameBuffer(int w, int h) : width(w), height(h)
	{
		framebuffer = 0;
		colorTexture = 0;
		rboDepthStencil = 0;
		SetFramebuffer();
	}

	OpenGLFrameBuffer::~OpenGLFrameBuffer()
	{
		glDeleteFramebuffers(1, &framebuffer);
		glDeleteTextures(1, &colorTexture);
		glDeleteRenderbuffers(1, &rboDepthStencil);
	}

	void OpenGLFrameBuffer::Bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
		glViewport(0, 0, width, height);
	}

	void OpenGLFrameBuffer::Unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void OpenGLFrameBuffer::SetFramebuffer()
	{
		if (framebuffer > 0)
		{
			glDeleteFramebuffers(1, &framebuffer);
			glDeleteTextures(1, &colorTexture);
			glDeleteTextures(1, &normalTexture);
			glDeleteTextures(1, &depthTexture);
			glDeleteRenderbuffers(1, &rboDepthStencil);
		}

		glGenFramebuffers(1, &framebuffer);
		glGenRenderbuffers(1, &renderedBufferRenderer);
		glGenRenderbuffers(1, &depthRenderbuffer);

		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
		glBindRenderbuffer(GL_RENDERBUFFER, renderedBufferRenderer);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA8, width, height);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, renderedBufferRenderer);

		glBindRenderbuffer(GL_RENDERBUFFER, depthRenderbuffer);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthRenderbuffer);

		glGenTextures(1, &colorTexture);
		glBindTexture(GL_TEXTURE_2D, colorTexture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// Attach it to currently bound framebuffer object
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorTexture, 0);

		glGenTextures(1, &normalTexture);
		glBindTexture(GL_TEXTURE_2D, normalTexture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// Attach it to currently bound framebuffer object
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, normalTexture, 0);

		glGenTextures(1, &depthTexture);
		glBindTexture(GL_TEXTURE_2D, depthTexture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// Attach it to currently bound framebuffer object
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTexture, 0);

		glBindTexture(GL_TEXTURE_2D, 0);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		GLenum err = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		if (err != GL_FRAMEBUFFER_COMPLETE)
			HS_CORE_ERROR("Framebuffer is Incomplete. Error {0}", glGetString(err));

	}

	void OpenGLFrameBuffer::Resize(int w, int h)
	{
		if (w != width || height != h)
		{
			width = w;
			height = h;
			SetFramebuffer();
		}
	}

	void OpenGLFrameBuffer::GetColorData(unsigned int* buffer, int channels)
	{
		buffer = new unsigned int[width * height * channels];
		glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
	}

	void OpenGLFrameBuffer::GetNormalsData(void* buffer)
	{
		glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, &buffer);
	}

	void OpenGLFrameBuffer::GetDepthData(void* buffer)
	{
		glReadPixels(0, 0, width, height, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, &buffer);
	}
}
