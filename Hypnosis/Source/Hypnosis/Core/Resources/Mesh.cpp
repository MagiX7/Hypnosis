#include "Mesh.h"

#include "Hypnosis/Renderer/VertexArray.h"
#include "Hypnosis/Renderer/VertexBuffer.h"
#include "Hypnosis/Renderer/IndexBuffer.h"

namespace Hypnosis {

	Mesh::Mesh(std::vector<Vertex> verts, std::vector<uint32_t> inds) : vertices(verts), indices(inds)
	{
		SetBuffers();
	}

	Mesh::~Mesh()
	{
	}

	void Mesh::Draw()
	{
		vao->Bind();
		ibo->Bind();
		glDrawElements(GL_TRIANGLES, ibo->GetCount(), GL_UNSIGNED_INT, 0);
		ibo->Unbind();
		vao->Unbind();
	}

	void Mesh::SetBuffers()
	{
		vao = VertexArray::Create();

		vbo.reset();
		vbo = VertexBuffer::Create(vertices.data(), vertices.size() * sizeof(Vertex));

		vbo->SetLayout({
			{ShaderDataType::VEC3F, "position"},
			{ShaderDataType::VEC3F, "normals"},
			{ShaderDataType::VEC2F, "texCoords"},
			{ShaderDataType::VEC3F, "tangents"},
			{ShaderDataType::VEC3F, "biTangents"},
		});
		vao->AddVertexBuffer(vbo);
		
		ibo = IndexBuffer::Create(&indices[0], indices.size());
		vao->SetIndexBuffer(ibo);

	}
}