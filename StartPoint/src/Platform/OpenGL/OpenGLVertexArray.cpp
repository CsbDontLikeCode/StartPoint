#include <sppch.h>
#include "OpenGLVertexArray.h"
#include <glad/glad.h>

namespace StartPoint {

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Float:				return GL_FLOAT;
		case ShaderDataType::Float2:			return GL_FLOAT;
		case ShaderDataType::Float3:			return GL_FLOAT;
		case ShaderDataType::Float4:			return GL_FLOAT;
		case ShaderDataType::Mat3:				return GL_FLOAT;
		case ShaderDataType::Mat4:				return GL_FLOAT;
		case ShaderDataType::Int:				return GL_INT;
		case ShaderDataType::Int2:				return GL_INT;
		case ShaderDataType::Int3:				return GL_INT;
		case ShaderDataType::Int4:				return GL_INT;
		case ShaderDataType::Bool:				return GL_BOOL;
		}

		SP_CORE_ASSERT(false, "Unknown ShaderDataType~");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_RendererID);

	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
		// Bind vertex array before bind vertex buffer
		glBindVertexArray(m_RendererID);

		vertexBuffer->Bind();
		unsigned int index = 0;
		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& i : layout) {
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index,
				i.GetElementCount(),
				ShaderDataTypeToOpenGLBaseType(i.Type),
				i.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)i.Offset);
			index++;
		}

		m_VertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		// Bind vertex array before bind index buffer
		glBindVertexArray(m_RendererID);

		indexBuffer->Bind();
		m_IndexBuffer = indexBuffer;
	}

}