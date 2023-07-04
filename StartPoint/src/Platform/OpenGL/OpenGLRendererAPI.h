#pragma once
#include <StartPoint/Renderer/RendererAPI.h>

namespace StartPoint {
	
	class OpenGLRendererAPI : public RendererAPI 
	{
	public:
		virtual void SetClearColor(const glm::vec4& color) const override;
		virtual void Clear() const override;

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;
	};

}