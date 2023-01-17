#pragma once

#include "Hypnosis/Renderer/FrameBuffer.h"

typedef unsigned int GLuint;

namespace Hypnosis {

	class OpenGLFrameBuffer : public FrameBuffer
	{
	public:
		OpenGLFrameBuffer(int w, int h);
		~OpenGLFrameBuffer();

		void Bind();
		void Unbind();

		void SetFramebuffer();
		void Resize(int w, int h);

		void GetColorData(unsigned int* buffer, int channels);
		void GetNormalsData(void* buffer);
		void GetDepthData(void* buffer);

		virtual inline unsigned int GetId() const override { return framebuffer; }
		virtual inline unsigned int GetColorId() const override { return colorTexture; }
		virtual inline unsigned int GetNormalsId() const override { return normalTexture; }
		virtual inline unsigned int GetDepthId() const override { return depthTexture; }
		virtual inline int GetWidth() const override { return width; }
		virtual inline int GetHeight() const override { return height; }

	private:
		int width;
		int height;

		GLuint framebuffer;
		GLuint quadFramebuffer;
		GLuint renderedBufferRenderer;
		GLuint depthRenderbuffer;

		GLuint rboDepthStencil;
		GLuint colorTexture;
		GLuint normalTexture;
		GLuint depthTexture;
	};

}