#include "Renderer.h"
#include "Hypnosis/Core/Log.h"

#include "VertexBuffer.h"
#include "Shader.h"

#include "Hypnosis/Core/Resources/Model.h"

#include <glad/glad.h>

namespace Hypnosis {

	struct RendererData
	{
		const uint32_t maxTris = 20000;
		const uint32_t maxVertices = maxTris * 4;
		const uint32_t maxIndices = maxTris * 6;

		Ref<VertexArray> triVertexArray;
		Ref<Shader> pbrShader;
		Ref<Texture2D> texture;

		uint32_t trisIndexCount = 0;

		Vertex* vertexBufferBase = nullptr;
		Vertex* vertexBufferPtr = nullptr;
	};

	static RendererData* data;

	Renderer::Renderer()
	{
	}

	Renderer::~Renderer()
	{
	}

	void Renderer::Init()
	{
		// Init API
		RenderCommand::Init();

		data = new RendererData();
		data->triVertexArray = VertexArray::Create();

		Ref<VertexBuffer> vbo = VertexBuffer::Create(data->maxVertices * sizeof(Vertex));
		vbo->SetLayout({
			{ShaderDataType::VEC3F, "position"},
			{ShaderDataType::VEC3F, "normals"},
			{ShaderDataType::VEC2F, "texCoords"},
			{ShaderDataType::VEC3F, "tangents"},
			{ShaderDataType::VEC3F, "biTangents"},
		});
		data->triVertexArray->AddVertexBuffer(vbo);


		data->vertexBufferBase = new Vertex[data->maxVertices];
		

		uint32_t* indices = new uint32_t[data->maxIndices];
		Ref<IndexBuffer> ibo = IndexBuffer::Create(indices, data->maxIndices);
		data->triVertexArray->SetIndexBuffer(ibo);
		delete[] indices;
		
		data->pbrShader = Shader::Create("Assets/Shaders/PBR.shader");
		// Bind textures??

	}

	void Renderer::ShutDown()
	{
	}

	void Renderer::BeginScene()
	{
		// TODO: Bind shader and pass the matrices

		data->vertexBufferPtr = data->vertexBufferBase;

	}

	void Renderer::EndScene()
	{

	}

	void Renderer::Submit(const Ref<VertexArray>& vertexArray)
	{
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}

}