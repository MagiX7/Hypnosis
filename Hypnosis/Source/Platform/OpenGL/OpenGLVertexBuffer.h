#pragma once

#include "Hypnosis/Renderer/VertexBuffer.h"

//#include "Hypnosis/Renderer/BufferLayout.h"

#include "glad/glad.h"
#include "glm/vec3.hpp"
#include "glm/gtc/type_ptr.hpp"

namespace Hypnosis {

	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		//OpenGLVertexBuffer();
		//OpenGLVertexBuffer(float* vertices, int count);
		OpenGLVertexBuffer(Vertex* vertices, uint32_t size);
		OpenGLVertexBuffer(uint32_t size);
		virtual ~OpenGLVertexBuffer();

		void SetData(void* vertices, uint32_t size);

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual const BufferLayout& GetLayout() const override { return layout; }
		// Make sure to do this BEFORE adding the VertexBuffer into the VertexArray.
		virtual void SetLayout(const BufferLayout& l) override { layout = l; }


	private:
		GLuint vbo;
		uint32_t count;
		BufferLayout layout;
	};

}