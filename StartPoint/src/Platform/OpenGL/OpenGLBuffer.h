#pragma once
#include "../../StartPoint/Renderer/Buffer.h"

namespace StartPoint {

	class OpenGLVertexBuffer : public VertexBuffer {
	public:
		OpenGLVertexBuffer(float* vertices, unsigned int size);
		OpenGLVertexBuffer(uint32_t size);

		virtual ~OpenGLVertexBuffer();

		virtual void Bind() const override;

		virtual void Unbind() const override;

		virtual void SetData(const void* data, uint32_t size) override;

		virtual const BufferLayout& GetLayout() const override;

		virtual void SetLayout(const BufferLayout& layout) override;

		
	private:
		unsigned int m_RendererID;

		BufferLayout m_Layout;
	};

	class OpenGLIndexBuffer : public IndexBuffer {
	public:
		OpenGLIndexBuffer(unsigned int* indices, unsigned int size);

		virtual ~OpenGLIndexBuffer();

		virtual void Bind() const override;

		virtual void Unbind() const override;

		virtual unsigned int GetCount() const override;
	private:
		unsigned int m_RendererID;
		unsigned int m_Count;
	};

}