#pragma once
#include "RendererAPI.h"

namespace StartPoint {

	class RenderCommand{
	public:
		inline static void Init() 
		{
			s_RendererAPI->Init();
		}

		inline static void SetViewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height) 
		{
			s_RendererAPI->SetViewport(x, y, width, height);
		}

		inline static void SetClearColor(const glm::vec4& color) 
		{
			s_RendererAPI->SetClearColor(color);
		}

		inline static void Clear() 
		{
			s_RendererAPI->Clear();
		}

		inline static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray, uint32_t count = 0) 
		{
			s_RendererAPI->DrawIndexed(vertexArray, count);
		}

		inline static void DrawLines(const std::shared_ptr<VertexArray>& vertexArray, uint32_t count)
		{
			s_RendererAPI->DrawLines(vertexArray, count);
		}

		inline static void SetLineWidth(float width)
		{
			s_RendererAPI->SetLineWidth(width);
		}
	private:
		static RendererAPI* s_RendererAPI;
	};

}