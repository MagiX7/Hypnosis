#pragma once

#include "Vertex.h"
#include "BufferLayout.h"

#include <memory>

namespace Hypnosis {

	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() {}

		//virtual void SetData(Vertex* vertex) = 0;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static std::shared_ptr<VertexBuffer> Create(Vertex* vertices, uint32_t size);

		virtual const BufferLayout& GetLayout() const = 0;
		virtual void SetLayout(const BufferLayout& layout) = 0;

	};

}