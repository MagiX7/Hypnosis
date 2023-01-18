#pragma once

#include "Hypnosis/Renderer/VertexArray.h"

#include <glad/glad.h>

#include <vector>

namespace Hypnosis {

	static GLenum GetOpenGLRawTypeFromShaderDataType(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::FLOAT:  return GL_FLOAT;
		case ShaderDataType::VEC2F:  return GL_FLOAT;
		case ShaderDataType::VEC3F:  return GL_FLOAT;
		case ShaderDataType::VEC4F:  return GL_FLOAT;
		case ShaderDataType::MAT3:	 return GL_FLOAT;
		case ShaderDataType::MAT4:	 return GL_FLOAT;
		case ShaderDataType::INT:	 return GL_INT;
		case ShaderDataType::VEC2I:	 return GL_INT;
		case ShaderDataType::VEC4I:	 return GL_INT;
		case ShaderDataType::VEC3I:	 return GL_INT;
		case ShaderDataType::BOOL:	 return GL_BOOL;
		}
		return 0;
	};

	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();

		void Bind() const;
		void Unbind() const;

		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuf)  override;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuf) override;

		std::vector<Ref<VertexBuffer>>& GetVertexBuffers() { return vertexBuffers; }
		virtual const Ref<IndexBuffer>& GetIndexBuffer() override { return indexBuffer; }

	private:
		uint32_t vao;

		std::vector<Ref<VertexBuffer>> vertexBuffers;
		Ref<IndexBuffer> indexBuffer;
	};
}