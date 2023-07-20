#pragma once
#include <StartPoint/Renderer/RendererAPI.h>

namespace StartPoint {
	
	class OpenGLRendererAPI : public RendererAPI 
	{
	public:
		virtual void Init() override;
		virtual void SetViewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height) override;
		virtual void SetClearColor(const glm::vec4& color) const override;
		virtual void Clear() const override;

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray, uint32_t indexCout = 0) override;
	};

}