#pragma once

#include "Hypnosis/Core/Core.h"

#include "Hypnosis/Renderer/Vertex.h"

#include <glm/vec3.hpp>
#include <vector>
#include <memory>

namespace Hypnosis {

	class VertexArray;
	class VertexBuffer;
	class IndexBuffer;

	class Mesh
	{
	public:
		Mesh(std::vector<Vertex> verts, std::vector<uint32_t> inds);
		~Mesh();

		void Draw();

		inline const std::vector<Vertex>& GetVertices() { return vertices; }

		inline const Ref<VertexArray>& GetVertexArray() { return vao; }

	private:
		void SetBuffers();

	private:
		std::vector<Vertex> vertices;
		std::vector<uint32_t> indices;

		Ref<VertexArray> vao;
		Ref<VertexBuffer> vbo;
		Ref<IndexBuffer> ibo;
	};

}