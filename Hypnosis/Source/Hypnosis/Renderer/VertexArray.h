#pragma once

#include "VertexBuffer.h"
#include "IndexBuffer.h"

#include <memory>

namespace Hypnosis {

	class VertexArray
	{
	public:

		virtual ~VertexArray() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) = 0;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) = 0;

		virtual const Ref<IndexBuffer>& GetIndexBuffer() = 0;

		static Ref<VertexArray> Create();
	};

}