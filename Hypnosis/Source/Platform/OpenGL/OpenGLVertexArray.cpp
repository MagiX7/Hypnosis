#include "OpenGLVertexArray.h"
#include "OpenGLVertexBuffer.h"

#include <glad/glad.h>

namespace Hypnosis {

    OpenGLVertexArray::OpenGLVertexArray()
    {
        // We do not bind it here because if we later create a vertex array and its bound, they are linked together and that may be dangerous.
        glGenVertexArrays(1, &vao);
    }

    OpenGLVertexArray::~OpenGLVertexArray()
    {
        glDeleteVertexArrays(1, &vao);
        vertexBuffers.clear();
    }

    void OpenGLVertexArray::Bind() const
    {
        glBindVertexArray(vao);
    }

    void OpenGLVertexArray::Unbind() const
    {
        glBindVertexArray(0);
    }

    // This should be called AFTER setting the layout to the VertexBuffer.
    void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuf)
    {
        glBindVertexArray(vao);
        vertexBuf->Bind();

        if (vertexBuf->GetLayout().GetElements().size() > 0)
        {
            uint32_t index = 0;
            const auto& layout = vertexBuf->GetLayout();
            int offset = 0;
            for (const auto& element : layout.GetElements())
            {
                glVertexAttribPointer(index, element.GetComponentCount(),
                    GetOpenGLRawTypeFromShaderDataType(element.type),
                    element.normalized ? GL_TRUE : GL_FALSE,
                    layout.GetStride(),
                    (void*)(offset * sizeof(GetOpenGLRawTypeFromShaderDataType(element.type))));
                glEnableVertexAttribArray(index);
                offset += element.GetComponentCount();
                index++;
            }
            vertexBuffers.push_back(vertexBuf);
        }
    }

    void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuf)
    {
        glBindVertexArray(vao);
        indexBuf->Bind();
        indexBuffer = indexBuf;
    }

}