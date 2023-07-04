#include <sppch.h>
#include "RendererAPI.h"

namespace StartPoint{

	RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;

	void RendererAPI::SetClearColor(const glm::vec4& color) const
	{
	}

	void RendererAPI::Clear() const
	{
	}

	void RendererAPI::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
	{

	}

}