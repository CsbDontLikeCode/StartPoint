#include <sppch.h>
#include "VertexArray.h"
#include "Renderer.h"
#include "../../Platform/OpenGL/OpenGLVertexArray.h"

namespace StartPoint {

	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI()) 
		{
		case RendererAPI::API::None:			SP_CORE_ASSERT(false, "RendererAPI None is not suppurted"); return nullptr;
		case RendererAPI::API::OpenGL:			return std::make_shared<OpenGLVertexArray>();
		}

		SP_CORE_ASSERT(false, "Unknow RendererAPI!");
		return nullptr;
	}
}