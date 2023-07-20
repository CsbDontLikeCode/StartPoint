#include <sppch.h>
#include <glad/glad.h>

#include "OpenGLRendererAPI.h"

namespace StartPoint {

	void OpenGLRendererAPI::Init()
	{
		// Enable deep testing
		glEnable(GL_DEPTH_TEST);

		// Enable textre blend
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		
	}

	void OpenGLRendererAPI::SetViewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height)
	{
		glViewport(x, y, width, height);
	}

	void OpenGLRendererAPI::SetClearColor(const glm::vec4& color) const
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRendererAPI::Clear() const
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray, uint32_t indexCount)
	{
		uint32_t count = (indexCount == 0  ? vertexArray->GetIndexBuffer()->GetCount() : indexCount);
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

}