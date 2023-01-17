#pragma once

#include <memory>

namespace Hypnosis {

	class FrameBuffer
	{
	public:
		virtual ~FrameBuffer() {};

		static std::shared_ptr<FrameBuffer> Create(int w, int h);

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual void SetFramebuffer() = 0;
		virtual void Resize(int w, int h) = 0;

		virtual unsigned int GetId() const = 0;
		virtual unsigned int GetColorId() const = 0;
		virtual unsigned int GetNormalsId() const = 0;
		virtual unsigned int GetDepthId() const = 0;

		virtual int GetWidth() const = 0;
		virtual int GetHeight() const = 0;

	};

}
