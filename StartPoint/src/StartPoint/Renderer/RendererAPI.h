#pragma once
#include <glm/glm.hpp>
#include "VertexArray.h"

namespace StartPoint {

	class RendererAPI 
	{
	public:
		enum class API 
		{
			None = 0,
			OpenGL = 1
		};

		static API s_API;
	public:
		virtual void Init() = 0;
		virtual void SetViewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height) = 0;
		virtual void SetClearColor(const glm::vec4& color) const = 0;
		virtual void Clear() const = 0;

		//virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) = 0;
		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray, uint32_t indexCount = 0) = 0;

		inline static API GetAPI() { return s_API; }
	};

}