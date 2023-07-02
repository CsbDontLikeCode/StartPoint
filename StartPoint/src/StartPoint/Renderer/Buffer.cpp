#include <sppch.h>
#include "Buffer.h"

#include "Renderer.h"
#include "../Log.h"
#include "../../Platform/OpenGL/OpenGLBuffer.h"

namespace StartPoint {

	VertexBuffer* VertexBuffer::Create(float* vertices, unsigned int size)
	{
		switch (Renderer::GetAPI()) {
		case RendererAPI::None:			SP_CORE_ASSERT(false, "RendererAPI None is not suppurted"); return nullptr;
		case RendererAPI::OpenGL:		return new OpenGLVertexBuffer(vertices, size);
		}

		SP_CORE_ASSERT(false,  "Unknow RendererAPI!");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(unsigned int* indices, unsigned int size)
	{
		switch (Renderer::GetAPI()) {
		case RendererAPI::None:			SP_CORE_ASSERT(false, "RendererAPI None is not suppurted"); return nullptr;
		case RendererAPI::OpenGL:		return new OpenGLIndexBuffer(indices, size);
		}

		SP_CORE_ASSERT(false, "Unknow RendererAPI!");
		return nullptr;
	}

}