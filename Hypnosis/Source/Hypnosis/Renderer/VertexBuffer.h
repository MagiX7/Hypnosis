#pragma once

#include "Hypnosis/Core/Core.h"

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

		static Ref<VertexBuffer> Create(uint32_t size);
		static Ref<VertexBuffer> Create(Vertex* vertices, uint32_t size);

		virtual const BufferLayout& GetLayout() const = 0;
		virtual void SetLayout(const BufferLayout& layout) = 0;

	};

}