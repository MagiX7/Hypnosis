#pragma once

#include "Hypnosis/Renderer/VertexArray.h"

#include <vector>

namespace Hypnosis {

	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();

		void Bind() const;
		void Unbind() const;

		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuf)  override;
		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuf) override;

		std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() { return vertexBuffers; }
		std::shared_ptr<IndexBuffer> GetIndexBuffer() { return indexBuffer; }

	private:
		uint32_t vao;

		std::vector<std::shared_ptr<VertexBuffer>> vertexBuffers;
		std::shared_ptr<IndexBuffer> indexBuffer;
	};
}