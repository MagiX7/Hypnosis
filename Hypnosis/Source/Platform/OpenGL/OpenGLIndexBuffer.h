#pragma once

#include "Hypnosis/Renderer/IndexBuffer.h"

#include <glad/glad.h>

//#include <utility>

namespace Hypnosis {

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer();
		OpenGLIndexBuffer(const uint32_t* indices, uint32_t count);
		virtual ~OpenGLIndexBuffer();

		void SetData(const uint32_t* indices, uint32_t count);
		void Bind() const;
		void Unbind() const;

		virtual uint32_t GetCount() const { return count; }
		//virtual const uint32_t& GetCount() const { return count; }
		inline const GLuint& GetID() const { return ibo; }


	private:
		GLuint ibo;
		uint32_t count;
	};


}